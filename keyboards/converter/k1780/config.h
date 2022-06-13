
#pragma once

#include "config_common.h"

#define PRODUCT           K1780 keyboard converter

#define MATRIX_ROWS       13
#define MATRIX_COLS       8

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define SERIAL_UART_BAUD 666
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT() do { \
  /* baud rate */ \
  UBRR1L = (uint8_t)SERIAL_UART_UBRR; \
  /* baud rate */ \
  UBRR1H = (uint16_t)SERIAL_UART_UBRR >> 8; \
  /* enable TX and RX */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1); \
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
} while(0)
