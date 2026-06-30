# This board ships with an APM32F072 (Geehy STM32F072 clone), whose ROM DFU
# bootloader enumerates as 314b:0106 instead of ST's 0483:df11. Override the
# stock stm32-dfu setting so QK_BOOT and `:flash` target the APM32 bootloader.
BOOTLOADER = apm32-dfu
