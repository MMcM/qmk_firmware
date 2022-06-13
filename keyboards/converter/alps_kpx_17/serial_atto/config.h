
#pragma once

#include "config_common.h"
                          
#define PRODUCT           Alps KP-17S keypad converter

#define MATRIX_ROWS       5
#define MATRIX_COLS       4

#define KPX_17S

#define SERIAL_UART_BAUD 1200
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* 8-bit data */ \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);
