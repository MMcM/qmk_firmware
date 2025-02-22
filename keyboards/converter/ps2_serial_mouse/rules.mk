CUSTOM_MATRIX = yes

PS2_DRIVER = interrupt
UART_DRIVER_REQUIRED = yes

SRC = matrix.c led.c serial_mouse.c

SERIAL_MOUSE_MICROSOFT_ENABLE ?= yes
SERIAL_MOUSE_MOUSESYSTEMS_ENABLE ?= no

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
