MCU = atmega32u4

BOOTLOADER = caterina

CUSTOM_MATRIX = yes

SRC = matrix.c

HARDWARE_SERIAL = yes
SRC += protocol/serial_uart.c
