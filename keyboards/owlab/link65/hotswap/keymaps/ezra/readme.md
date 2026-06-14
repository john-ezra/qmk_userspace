# Owlab Link65 Hotswap Ezra Keymap

## Flashing

Enter the bootloader by holding `B` while plugging in USB.

Build and flash with:

```sh
make owlab/link65/hotswap:ezra:flash
```

If `dfu-util` reports `LIBUSB_ERROR_ACCESS`, the board is detected but the current user does not have permission to open the USB device. Use the permission-safe command:

```sh
sudo -v
make owlab/link65/hotswap:ezra:flash DFU_UTIL="sudo dfu-util" DFU_ARGS="-d 1688:2220 -a 0 -s 0x08006000:leave"
```

This board uses an STM32duino-style bootloader with firmware starting at `0x08006000`. Do not use QMK Toolbox for this board; it can flash to the wrong address.

`QK_BOOT` is intentionally not mapped in this keymap. Use the hardware bootloader entry method instead.
