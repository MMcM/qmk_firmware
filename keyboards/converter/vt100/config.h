
#pragma once

#include "config_common.h"

#define PRODUCT           VT100 keyboard converter

#define MATRIX_ROWS       8
#define MATRIX_COLS       16

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define VT100_LED_MASK 0x3F;
#define VT100_START_SCAN (1<<6)
#define VT100_SPEAKER (1<<7)

#define SERIAL_UART_BAUD 7812
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT() do { \
  /* baud rate */ \
  UBRR1L = SERIAL_UART_UBRR; \
  /* baud rate */ \
  UBRR1H = SERIAL_UART_UBRR >> 8; \
  /* enable TX and RX */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1); \
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
} while(0)

// Both Shift keys send the same code, so make COMMAND be both NO-SCROLL + LINE_FEED keys instead.
#define IS_COMMAND() (get_mods() == MOD_MASK_ALT)
