
#pragma once

#include "config_common.h"

#define PRODUCT           Sperry-Univac UTS keyboard converter

#define MATRIX_ROWS       9
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* 8 data bits, 2 stop bits, odd parity */ \
    UCSR1C = _BV(UPM11) | _BV(UPM10) | _BV(USBS1) | _BV(UCSZ11) | _BV(UCSZ10);
