
#pragma once

#include "config_common.h"

#define PRODUCT           Compaq numeric keypad converter
                          
#define MATRIX_ROWS       16
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_INIT_CUSTOM \
    /* enable RX only with interrupt */ \
    UCSR1B = _BV(RXEN1) | _BV(RXCIE1); \
    /* 8-bit data */ \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);
