MCU = atmega32u4

BOOTLOADER = caterina

WAIT_FOR_USB = yes
CUSTOM_MATRIX = yes

SRC = matrix.c led.c

HARDWARE_SERIAL = yes
SRC += protocol/serial_uart.c
