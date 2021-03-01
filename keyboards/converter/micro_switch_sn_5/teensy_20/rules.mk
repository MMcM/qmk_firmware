# Teensy
MCU = atmega32u4
BOOTLOADER = halfkay

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
WAIT_FOR_USB = yes
