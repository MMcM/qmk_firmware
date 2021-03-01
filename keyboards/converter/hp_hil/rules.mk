# Teensy
MCU = atmega32u4
BOOTLOADER = halfkay

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

SPLIT_KEYBOARD = no
WAIT_FOR_USB = yes
LAYOUTS_HAS_RGB = no
CUSTOM_MATRIX = yes

OPT_DEFS += -DMOUSE_ENABLE -DNO_SOF_EVENTS

SRC = matrix.c
