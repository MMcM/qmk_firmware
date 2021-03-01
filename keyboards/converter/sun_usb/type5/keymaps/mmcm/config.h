
#pragma once

#define SERIAL_UART_BAUD 1200
#define SERIAL_UART_INIT_CUSTOM \
  /* enable TX and RX with interrupt */ \
  UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);
