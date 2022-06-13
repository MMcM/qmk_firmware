
#pragma once

#include "config_common.h"

#ifndef NMB_TVI_RAW
#define PRODUCT           NMB Televideo keyboard converter
#else
#define PRODUCT           NMB Televideo (raw) keyboard converter
#endif

#ifdef NMB_TVI_RAW
#define MATRIX_ROWS       8
#else
#define MATRIX_ROWS       16
#endif
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_INIT_CUSTOM \
  /* enable TX and RX with interrupt */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

#ifndef NMB_TVI_RAW
// RESET on PD1
#define RESET_PIN PIND
#define RESET_PORT PORTD
#define RESET_DDR DDRD
#define RESET_MASK (1<<1)
#endif
