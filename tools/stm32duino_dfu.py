#!/usr/bin/env python3
"""Download a firmware image to an stm32duino DFU bootloader without resetting it.

The stm32duino bootloader ends every download in dfuMANIFEST-WAIT-RESET and
only runs the new image after a USB reset or a power cycle. dfu-util answers
that state with libusb_reset_device() whether or not -R was given
(dfu_load.c, dfuload_do_dnload). On the Mechlovin STM32F103 boards that reset
reboots the MCU straight into QMK while the host is still re-addressing the
port, QMK's USB stack then sits waiting for a bus reset that never comes, and
the xHCI recovery path the kernel runs for the unanswered SET_ADDRESS has
killed the ASMedia host controllers in this machine.

This tool speaks plain DFU 1.1 through Linux usbfs, stops once the bootloader
reports manifest, and leaves the power cycle to the user. Permissions come
from the same udev rules dfu-util relies on.

Usage: stm32duino_dfu.py FIRMWARE.bin
"""

from __future__ import annotations

import ctypes
import fcntl
import os
import struct
import sys
import time
from pathlib import Path

BOOTLOADER_VID = 0x1EAF
BOOTLOADER_PID = 0x0003
ALT_FLASH_0X8002000 = 2
TIMEOUT_MS = 5000
SYSFS_USB = Path("/sys/bus/usb/devices")

# DFU 1.1 section 6: class requests, bState, bStatus.
DFU_DNLOAD, DFU_GETSTATUS, DFU_CLRSTATUS, DFU_ABORT = 1, 3, 4, 6
REQUEST_OUT, REQUEST_IN = 0x21, 0xA1
STATE_NAMES = [
    "appIDLE", "appDETACH", "dfuIDLE", "dfuDNLOAD-SYNC", "dfuDNBUSY", "dfuDNLOAD-IDLE",
    "dfuMANIFEST-SYNC", "dfuMANIFEST", "dfuMANIFEST-WAIT-RESET", "dfuUPLOAD-IDLE", "dfuERROR",
]
DFU_IDLE, DFU_DNLOAD_SYNC, DFU_DNBUSY, DFU_DNLOAD_IDLE = 2, 3, 4, 5
DFU_MANIFEST_SYNC, DFU_MANIFEST, DFU_ERROR = 6, 7, 10
STATUS_NAMES = [
    "OK", "errTARGET", "errFILE", "errWRITE", "errERASE", "errCHECK_ERASED", "errPROG", "errVERIFY",
    "errADDRESS", "errNOTDONE", "errFIRMWARE", "errVENDOR", "errUSBR", "errPOR", "errUNKNOWN", "errSTALLEDPKT",
]


# usbfs ioctls, from include/uapi/linux/usbdevice_fs.h.
class CtrlTransfer(ctypes.Structure):
    _fields_ = [
        ("bRequestType", ctypes.c_uint8),
        ("bRequest", ctypes.c_uint8),
        ("wValue", ctypes.c_uint16),
        ("wIndex", ctypes.c_uint16),
        ("wLength", ctypes.c_uint16),
        ("timeout", ctypes.c_uint32),
        ("data", ctypes.c_void_p),
    ]


class SetInterface(ctypes.Structure):
    _fields_ = [("interface", ctypes.c_uint), ("altsetting", ctypes.c_uint)]


def _ioc(direction: int, nr: int, size: int) -> int:
    return (direction << 30) | (size << 16) | (ord("U") << 8) | nr


USBDEVFS_CONTROL = _ioc(3, 0, ctypes.sizeof(CtrlTransfer))
USBDEVFS_SETINTERFACE = _ioc(2, 4, ctypes.sizeof(SetInterface))
USBDEVFS_CLAIMINTERFACE = _ioc(2, 15, ctypes.sizeof(ctypes.c_uint))
USBDEVFS_RELEASEINTERFACE = _ioc(2, 16, ctypes.sizeof(ctypes.c_uint))


def dfu_interface(descriptors: bytes) -> tuple[int | None, int | None]:
    """Return (bInterfaceNumber, wTransferSize) of the DFU interface in a sysfs descriptor blob."""
    interface = transfer_size = None
    offset = 0
    while offset + 2 <= len(descriptors):
        length, kind = descriptors[offset], descriptors[offset + 1]
        if length == 0:
            break
        descriptor = descriptors[offset:offset + length]
        if kind == 0x04 and length >= 9 and descriptor[5] == 0xFE and descriptor[6] == 0x01:
            interface = descriptor[2]
        elif kind == 0x21 and length == 9 and interface is not None:
            transfer_size = struct.unpack_from("<H", descriptor, 5)[0]
        offset += length
    return interface, transfer_size


def find_bootloader() -> Path | None:
    for device in SYSFS_USB.iterdir():
        try:
            vid = int((device / "idVendor").read_text(), 16)
            pid = int((device / "idProduct").read_text(), 16)
        except (FileNotFoundError, ValueError):
            continue
        if (vid, pid) == (BOOTLOADER_VID, BOOTLOADER_PID):
            return device
    return None


def wait_for_bootloader() -> Path:
    device = find_bootloader()
    if device is None:
        print(
            f"Bootloader {BOOTLOADER_VID:04X}:{BOOTLOADER_PID:04X} not found. Make sure the board is in bootloader mode.\n"
            "Trying again every 0.5s (Ctrl+C to cancel)",
            flush=True,
        )
        while device is None:
            time.sleep(0.5)
            device = find_bootloader()
    return device


class DfuDevice:
    def __init__(self, sysfs: Path, alt: int):
        self.interface, self.transfer_size = dfu_interface((sysfs / "descriptors").read_bytes())
        if self.interface is None or not self.transfer_size:
            raise SystemExit(f"{sysfs.name}: no DFU interface with a transfer size in its descriptors")
        bus = int((sysfs / "busnum").read_text())
        address = int((sysfs / "devnum").read_text())
        self.fd = self._open(f"/dev/bus/usb/{bus:03d}/{address:03d}")
        fcntl.ioctl(self.fd, USBDEVFS_CLAIMINTERFACE, ctypes.c_uint(self.interface))
        fcntl.ioctl(self.fd, USBDEVFS_SETINTERFACE, SetInterface(self.interface, alt))

    @staticmethod
    def _open(node: str) -> int:
        # udev grants the uaccess ACL a moment after the device node appears.
        deadline = time.monotonic() + 2.0
        while True:
            try:
                return os.open(node, os.O_RDWR)
            except PermissionError:
                if time.monotonic() >= deadline:
                    raise
                time.sleep(0.1)

    def close(self) -> None:
        fcntl.ioctl(self.fd, USBDEVFS_RELEASEINTERFACE, ctypes.c_uint(self.interface))
        os.close(self.fd)

    def control(self, request_type: int, request: int, value: int, payload: bytes = b"", length: int = 0) -> bytes:
        size = max(len(payload), length)
        buffer = ctypes.create_string_buffer(payload, size) if size else None
        transfer = CtrlTransfer(
            request_type, request, value, self.interface, size, TIMEOUT_MS,
            ctypes.addressof(buffer) if buffer is not None else None,
        )
        transferred = fcntl.ioctl(self.fd, USBDEVFS_CONTROL, transfer)
        return buffer.raw[:transferred] if buffer is not None else b""

    def get_status(self) -> tuple[int, int, int]:
        """Return (bStatus, bwPollTimeout in ms, bState)."""
        status = self.control(REQUEST_IN, DFU_GETSTATUS, 0, length=6)
        if len(status) != 6:
            raise SystemExit(f"DFU_GETSTATUS returned {len(status)} bytes, expected 6")
        return status[0], int.from_bytes(status[1:4], "little"), status[4]

    def wait_state(self, busy_states: tuple[int, ...]) -> tuple[int, int]:
        """Poll DFU_GETSTATUS while the device reports one of busy_states; return (bStatus, bState)."""
        while True:
            status, poll_ms, state = self.get_status()
            if state not in busy_states:
                return status, state
            time.sleep(poll_ms / 1000)

    def settle_idle(self) -> None:
        """Bring a bootloader left in an error or mid-transfer state back to dfuIDLE."""
        status, _, state = self.get_status()
        if state == DFU_ERROR:
            self.control(REQUEST_OUT, DFU_CLRSTATUS, 0)
            status, _, state = self.get_status()
        if state != DFU_IDLE:
            self.control(REQUEST_OUT, DFU_ABORT, 0)
            status, _, state = self.get_status()
        if state != DFU_IDLE:
            raise SystemExit(f"bootloader is not idle ({describe(status, state)})")


def describe(status: int, state: int) -> str:
    state_name = STATE_NAMES[state] if state < len(STATE_NAMES) else f"state {state}"
    status_name = STATUS_NAMES[status] if status < len(STATUS_NAMES) else f"status {status}"
    return f"{state_name}, {status_name}"


def download(device: DfuDevice, image: bytes) -> int:
    device.settle_idle()

    block_size = device.transfer_size
    blocks = range(0, len(image), block_size)
    for block, offset in enumerate(blocks):
        device.control(REQUEST_OUT, DFU_DNLOAD, block, image[offset:offset + block_size])
        status, state = device.wait_state(busy_states=(DFU_DNLOAD_SYNC, DFU_DNBUSY))
        if state != DFU_DNLOAD_IDLE or status != 0:
            raise SystemExit(f"\ndownload failed at block {block} ({describe(status, state)})")
        sent = min(offset + block_size, len(image))
        print(f"\rDownloading {sent}/{len(image)} bytes", end="", flush=True)
    print()

    # Zero-length DNLOAD closes the transfer; the bootloader locks flash and
    # moves to manifest. It will report dfuMANIFEST-WAIT-RESET from here on.
    device.control(REQUEST_OUT, DFU_DNLOAD, len(blocks), b"")
    status, state = device.wait_state(busy_states=(DFU_MANIFEST_SYNC, DFU_MANIFEST))
    if status != 0:
        raise SystemExit(f"manifest failed ({describe(status, state)})")
    return state


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        raise SystemExit(f"usage: {Path(argv[0]).name} FIRMWARE.bin")
    image = Path(argv[1]).read_bytes()
    if not image:
        raise SystemExit(f"{argv[1]} is empty")

    sysfs = wait_for_bootloader()
    device = DfuDevice(sysfs, ALT_FLASH_0X8002000)
    try:
        print(f"Found bootloader on bus {sysfs.name}, interface {device.interface}, alt {ALT_FLASH_0X8002000}, "
              f"transfer size {device.transfer_size}")
        state = download(device, image)
    finally:
        device.close()

    state_name = STATE_NAMES[state] if state < len(STATE_NAMES) else f"state {state}"
    print(f"Download complete, bootloader reports {state_name}.")
    print("Unplug and replug the keyboard to start the new firmware.")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv))
    except KeyboardInterrupt:
        sys.exit(130)
