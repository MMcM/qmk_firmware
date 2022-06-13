
#pragma once

#include "config_common.h"

#define PRODUCT           Apollo keyboard converter

#define MATRIX_ROWS       8
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 1200
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* even parity, 8-bit data */ \
    UCSR1C = _BV(UPM11) | _BV(UCSZ11) | _BV(UCSZ10);
