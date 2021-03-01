# Teensy
MCU = atmega32u4
BOOTLOADER = halfkay

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

WAIT_FOR_USB = yes
CUSTOM_MATRIX = yes

PS2_USE_INT = yes
HARDWARE_SERIAL = yes

SRC = matrix.c led.c

SRC += protocol/serial_uart.c
