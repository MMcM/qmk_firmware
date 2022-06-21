
#pragma once

#include "config_common.h"

#define PRODUCT           PS2 keyboard with serial mouse converter
                          
#define MATRIX_ROWS       24
#define MATRIX_COLS       32

/*
 * PS/2 USART configuration for ATMega32U4
 */
#ifdef PS2_USE_USART
#error The UART is needed for the mouse; use PS2_USE_INT.
#endif


/*
 * PS/2 Interrupt configuration
 */
#ifdef PS2_USE_INT
/* uses INT1 for clock line(ATMega32U4) */
#define PS2_CLOCK_PIN   D1
#define PS2_DATA_PIN    D0

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT1);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define PS2_INT_VECT    INT1_vect
#endif


/*
 * PS/2 Busywait configuration
 */
#ifdef PS2_USE_BUSYWAIT
#define PS2_CLOCK_PIN   D1
#define PS2_DATA_PIN    D0
#endif

/*
 * Serial Mouse USART configuration for ATMega32U4
 */
#define SERIAL_UART_BAUD 1200
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* 8-bit data */ \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
    /* Turn on DTR via PC6 by setting T2IN low = space = asserted */ \
    DDRC |= (1 << 6);
