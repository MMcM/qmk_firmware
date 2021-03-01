
#pragma once

#include "config_common.h"

#define PRODUCT           NMB 110695 keyboard converter
#define DESCRIPTION       NMB 110695 keyboard converter
                          
#define MATRIX_ROWS       16
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_INIT_CUSTOM \
  /* enable TX and RX with interrupt */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

// RESET on PD1
#define RESET_PIN PIND
#define RESET_PORT PORTD
#define RESET_DDR DDRD
#define RESET_MASK (1<<1)
