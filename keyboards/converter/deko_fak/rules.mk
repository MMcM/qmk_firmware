# Teensy
MCU = atmega32u4
BOOTLOADER = halfkay

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

WAIT_FOR_USB = yes
CUSTOM_MATRIX = yes
# Should match Soarer's
PS2_USE_INT = yes

SRC = matrix.c led.c vfd.c
