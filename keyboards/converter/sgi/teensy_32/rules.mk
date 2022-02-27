# Teensy 3.2
MCU = MK20DX256
BOOTLOADER = halfkay

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

#SERIAL_MOUSE_MOUSESYSTEMS_ENABLE = yes
