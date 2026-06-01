#!/usr/bin/env python3
"""Incrementally update QMK userspace compile_commands.json."""

from __future__ import annotations

import argparse
import json
import os
import shlex
import subprocess
import sys
import tempfile
from pathlib import Path


def qmk_config_path(name: str) -> Path:
    result = subprocess.run(
        ["qmk", "config", "-ro", name],
        check=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    value = result.stdout.strip().split("=", 1)[-1]
    if not value or value == "None":
        raise SystemExit(f"qmk config {name} is not set")
    return Path(value).expanduser().resolve()


def parse_env(assignments: list[str]) -> dict[str, str]:
    env = {}
    for assignment in assignments:
        if "=" not in assignment:
            raise SystemExit(f"Invalid environment override: {assignment}")
        key, value = assignment.split("=", 1)
        if not key:
            raise SystemExit(f"Invalid environment override: {assignment}")
        env[key] = value
    return env


def load_userspace_targets(userspace: Path) -> list[tuple[str, str, dict[str, str]]]:
    qmk_json = userspace / "qmk.json"
    data = json.loads(qmk_json.read_text(encoding="utf-8"))
    targets = []

    for entry in data.get("build_targets", []):
        if isinstance(entry, list) and len(entry) in {2, 3}:
            keyboard, keymap = entry[0], entry[1]
            build_env = entry[2] if len(entry) == 3 else {}
            if not isinstance(keyboard, str) or not isinstance(keymap, str):
                raise SystemExit(f"Unsupported build target in {qmk_json}: {entry!r}")
            if not isinstance(build_env, dict):
                raise SystemExit(f"Unsupported build environment in {qmk_json}: {entry!r}")
            targets.append((keyboard, keymap, {str(k): str(v) for k, v in build_env.items()}))
        else:
            raise SystemExit(f"Unsupported build target in {qmk_json}: {entry!r}")

    return targets


def record_args(record: dict) -> list[str]:
    if isinstance(record.get("arguments"), list):
        return record["arguments"]
    if isinstance(record.get("command"), str):
        return shlex.split(record["command"])
    return []


def define_value(args: list[str], name: str) -> str | None:
    prefix = f"-D{name}="
    for arg in args:
        if arg.startswith(prefix):
            return arg[len(prefix) :].strip('"')
    return None


def record_target(record: dict) -> tuple[str | None, str | None]:
    args = record_args(record)
    return define_value(args, "QMK_KEYBOARD"), define_value(args, "QMK_KEYMAP")


def resolve_record_file(record: dict) -> Path | None:
    file = record.get("file")
    if not isinstance(file, str) or not file:
        return None

    path = Path(file).expanduser()
    if not path.is_absolute() and record.get("directory"):
        path = Path(record["directory"]) / path
    return path.resolve()


def keymap_c_path(record: dict) -> Path | None:
    value = define_value(record_args(record), "KEYMAP_C")
    if not value:
        return None

    path = Path(value).expanduser()
    if not path.is_absolute() and record.get("directory"):
        path = Path(record["directory"]) / path
    return path.resolve()


def synthesize_keymap_record(records: list[dict], keyboard: str, keymap: str) -> dict | None:
    candidates = [record for record in records if record_target(record) == (keyboard, keymap) and keymap_c_path(record)]
    if not candidates:
        return None

    candidates.sort(key=lambda record: 0 if str(record.get("file", "")).endswith("default_keyboard.c") else 1)
    base = candidates[0]
    keymap_path = keymap_c_path(base)
    if any(resolve_record_file(record) == keymap_path for record in records):
        return None

    source = base.get("file")
    args = list(record_args(base))
    replaced = False
    for index, arg in enumerate(args):
        if arg == source or arg.endswith("/default_keyboard.c"):
            args[index] = str(keymap_path)
            replaced = True
            break

    if not replaced:
        raise SystemExit(f"Could not find source argument for {keyboard}:{keymap}")

    record = {**base, "arguments": args, "file": str(keymap_path)}
    record.pop("command", None)
    return record


def load_compile_commands(path: Path) -> list[dict]:
    if not path.exists():
        return []
    return json.loads(path.read_text(encoding="utf-8"))


def write_compile_commands(path: Path, records: list[dict]) -> None:
    path.write_text(json.dumps(records, indent=4) + "\n", encoding="utf-8")


def generate_target_database(qmk_home: Path, userspace: Path, keyboard: str, keymap: str, env: dict[str, str]) -> list[dict]:
    old_cwd = Path.cwd()
    qmk_python = qmk_home / "lib" / "python"
    if not qmk_python.is_dir():
        raise SystemExit(f"Could not find QMK python library at {qmk_python}")

    os.environ["QMK_USERSPACE"] = str(userspace)
    os.environ.setdefault("ORIG_CWD", str(userspace))
    sys.path.insert(0, str(qmk_python))

    try:
        os.chdir(qmk_home)

        from qmk.build_targets import KeyboardKeymapBuildTarget
        from qmk.commands import build_environment
        from qmk.compilation_database import write_compilation_database

        qmk_env = build_environment([])
        qmk_env.update(env)

        target = KeyboardKeymapBuildTarget(keyboard, keymap)
        command = target.compile_command(dry_run=True, **qmk_env)

        with tempfile.TemporaryDirectory(prefix="qmk-compiledb-") as tempdir:
            output = Path(tempdir) / "compile_commands.json"
            ok = write_compilation_database(command=command, output_path=output, skip_clean=True, **qmk_env)
            if not ok:
                raise SystemExit(f"Failed to generate compile database for {keyboard}:{keymap}")
            records = load_compile_commands(output)
            keymap_record = synthesize_keymap_record(records, keyboard, keymap)
            if keymap_record:
                records.append(keymap_record)
            return records
    finally:
        os.chdir(old_cwd)


def merge_target(records: list[dict], target_records: list[dict], keyboard: str, keymap: str) -> list[dict]:
    records = [record for record in records if record_target(record) != (keyboard, keymap)]
    records.extend(target_records)
    return records


def main() -> int:
    userspace = Path(__file__).resolve().parents[1]

    parser = argparse.ArgumentParser(description="Update userspace compile_commands.json for QMK clangd support.")
    parser.add_argument("-kb", "--keyboard", help="Keyboard target, for example wilba_tech/wt65_h1")
    parser.add_argument("-km", "--keymap", help="Keymap name, for example ezra")
    parser.add_argument("-e", "--env", action="append", default=[], help="Build environment override, KEY=VALUE")
    parser.add_argument("--all", action="store_true", help="Refresh every target listed in qmk.json")
    parser.add_argument("--replace-all", action="store_true", help="Discard the existing compile database before writing")
    parser.add_argument("--qmk-home", type=Path, default=None, help="Path to qmk_firmware")
    args = parser.parse_args()

    if args.all:
        targets = load_userspace_targets(userspace)
    else:
        if not args.keyboard or not args.keymap:
            parser.error("-kb/--keyboard and -km/--keymap are required unless --all is used")
        targets = [(args.keyboard, args.keymap, parse_env(args.env))]

    qmk_home = (args.qmk_home or qmk_config_path("user.qmk_home")).expanduser().resolve()
    compile_commands = userspace / "compile_commands.json"
    records = [] if args.replace_all else load_compile_commands(compile_commands)

    for keyboard, keymap, env in targets:
        print(f"Updating compile_commands.json for {keyboard}:{keymap}")
        target_records = generate_target_database(qmk_home, userspace, keyboard, keymap, env)
        records = merge_target(records, target_records, keyboard, keymap)

    write_compile_commands(compile_commands, records)
    print(f"Wrote {compile_commands}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
