
#pragma once

#define SERIAL_UART_BAUD 600
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
  /* 8-bit data, odd parity */ \
  UCSR1C = _BV(UPM11) | _BV(UPM10) | _BV(UCSZ11) | _BV(UCSZ10); \
} while(0)
