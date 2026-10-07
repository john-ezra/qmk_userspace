RGBLIGHT_ENABLE = no

# Flash with tools/stm32duino_dfu.py instead of dfu-util: dfu-util resets the
# board unconditionally once the bootloader reports dfuMANIFEST-WAIT-RESET, the
# board does not answer the SET_ADDRESS that follows, and the kernel's recovery
# path has killed this machine's ASMedia xHCI controllers. The tool stops at
# manifest; unplug and replug the board to start the new firmware. See
# ../../../zed60/kaze_mini/keymaps/ezra/readme.md.
PROGRAM_CMD = python3 $(QMK_USERSPACE)/tools/stm32duino_dfu.py $(BUILD_DIR)/$(TARGET).bin
