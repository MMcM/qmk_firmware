# MCU name
MCU = MKL26Z64
USE_CHIBIOS_CONTRIB = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# There isn't enough heap space ("cannot move location counter backwards") with this and UART turned on.
CONSOLE_ENABLE = no
