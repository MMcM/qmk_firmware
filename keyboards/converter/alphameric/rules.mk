# Teensy
MCU = atmega32u4
BOOTLOADER = halfkay

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

WAIT_FOR_USB = yes
CUSTOM_MATRIX = yes

OPT_DEFS += -DNO_SOF_EVENTS

SRC = matrix.c ../xt_usb/xt_interrupt.c

