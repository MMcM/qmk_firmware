
#pragma once

#include "config_common.h"

#define VENDOR_ID         0xFEED
#define PRODUCT_ID        0x4060
#define DEVICE_VER        1
#define MANUFACTURER      QMK
#define PRODUCT           Cherry 4060-A keypad converter
#define DESCRIPTION       Cherry 4060-A keypad converter
                          
#define MATRIX_ROWS       8
#define MATRIX_COLS       4

#define SERIAL_UART_BAUD 9600
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
  /* 8-bit data */ \
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
} while(0)

#define LED_DRIVER_COUNT 1
#define LED_DRIVER_LED_COUNT 32

// Updated a row at a time as data received by keyboard.
#define LED_REFRESH_FREQUENCY ((SERIAL_UART_BAUD/10)/MATRIX_ROWS)
#define LED_MATRIX_MAXIMUM_BRIGHTNESS LED_REFRESH_FREQUENCY

// Up to 12 is supported elsewhere in code, but tends to be more distracting when used for this.
#define BACKLIGHT_LEVELS 4
