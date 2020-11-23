
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0x101E
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           PS2 keyboard with serial mouse converter
#define DESCRIPTION       PS2 keyboard with serial mouse keyboard converter
                          
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
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   1

#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0

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
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   1

#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0
#endif

/*
 * Serial Mouse USART configuration for ATMega32U4
 */
#define SERIAL_UART_BAUD 1200
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_RXD_VECT    USART1_RX_vect
#define SERIAL_UART_INIT() do { \
  /* baud rate */ \
  UBRR1L = (uint8_t)SERIAL_UART_UBRR; \
  /* baud rate */ \
  UBRR1H = (uint16_t)SERIAL_UART_UBRR >> 8; \
  /* enable TX and RX with interrupt */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
  /* 7-bit data, two stop bits (ignored on receive) */ \
  UCSR1C = _BV(UCSZ11) | _BV(USBS1); \
  /* Turn on DTR via PC6 */ \
  DDRC |= (1 << 6); \
  PORTC |= (1 << 6); \
} while(0)
