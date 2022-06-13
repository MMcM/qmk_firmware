
#pragma once

#include "config_common.h"

#define PRODUCT           Cherry 4060-A keypad converter
                          
#define MATRIX_ROWS       8
#define MATRIX_COLS       4

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* 8-bit data */ \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

#define DRIVER_LED_TOTAL 32

// Updated a row at a time as data received by keyboard.
#define LED_REFRESH_FREQUENCY ((SERIAL_UART_BAUD/10)/MATRIX_ROWS)
#define LED_MATRIX_MAXIMUM_BRIGHTNESS LED_REFRESH_FREQUENCY

// Up to 12 is supported elsewhere in code, but tends to be more distracting when used for this.
#define BACKLIGHT_LEVELS 4
//#define LED_MATRIX_KEYPRESSES
