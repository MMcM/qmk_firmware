# Teensy
MCU = atmega32u4

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

BOOTLOADER = caterina

EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
WAIT_FOR_USB = yes
