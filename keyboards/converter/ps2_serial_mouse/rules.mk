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

SERIAL_MOUSE_MICROSOFT_ENABLE ?= no
SERIAL_MOUSE_MOUSESYSTEMS_ENABLE ?= yes

ifeq ($(strip $(SERIAL_MOUSE_MICROSOFT_ENABLE)), yes)
    SRC += serial_mouse_microsoft.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MICROSOFT \
                -DMOUSE_ENABLE
endif

ifeq ($(strip $(SERIAL_MOUSE_MOUSESYSTEMS_ENABLE)), yes)
    SRC += serial_mouse_mousesystems.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MOUSESYSTEMS \
                -DMOUSE_ENABLE
endif
