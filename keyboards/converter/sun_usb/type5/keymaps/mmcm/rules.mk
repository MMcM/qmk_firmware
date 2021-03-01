HARDWARE_SERIAL = yes

# Need to start over
SRC = matrix.c led.c

ifdef HARDWARE_SERIAL
  SRC += protocol/serial_uart.c
  OPT_DEFS += -DHARDWARE_SERIAL
else
  SRC += protocol/serial_soft.c
endif
