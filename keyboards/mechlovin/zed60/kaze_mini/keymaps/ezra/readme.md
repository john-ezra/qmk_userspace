# NRD Kaze Mini (Mechlovin Zed60 Hotswap) Ezra Keymap

## Flashing

Enter the bootloader by holding `Esc` while plugging in USB, or press the reset button on the back of the PCB. It enumerates as `LeafLabs Zed60 Boot` (`1EAF:0003`).

```sh
qmk flash -kb mechlovin/zed60/kaze_mini -km ezra
```

This keymap's `rules.mk` sets `PROGRAM_CMD` to `tools/stm32duino_dfu.py` so dfu-util is never run for this board. The download ends with the bootloader reporting `dfuMANIFEST-WAIT-RESET` and nothing resets it. **Unplug and replug the keyboard to start the new firmware.**

## Why not dfu-util

dfu-util resets the board as soon as the bootloader reports `dfuMANIFEST-WAIT-RESET` (`dfu_load.c`, `dfuload_do_dnload`); `-R` only adds a second reset at the end, so dropping it changes nothing. The stm32duino bootloader answers that reset with a hard MCU reset (`dfuUpdateByReset`) and boots into QMK, whose USB stack only starts answering after the next bus reset. The host does not send one; it sends `SET_ADDRESS`, which goes unanswered. The kernel's recovery path (`device not accepting address`, `invalid context state for evaluate context command`, a second port reset) wedged both ASMedia controllers in this machine (`1022:43fd`, subsystem `1b21:1142`): once as `HC died`, twice as a port stuck on `-110` timeouts until the driver was rebound.

The stock Mechlovin' image fails the same `SET_ADDRESS` the same way after a dfu-util download; the image is not the variable. A power cycle instead of a reset gives the host a real disconnect and a fresh enumeration, which is the path this board has always survived. The cold-plug `device descriptor read/64, error -71` line in the kernel log is normal for this board with any image; the host retries and succeeds.
