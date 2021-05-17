
#pragma once

#define SERIAL_UART_BAUD 9600
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* odd parity, 8-bit data */ \
    UCSR1C = _BV(UPM11) | _BV(UPM10) | _BV(UCSZ11) | _BV(UCSZ10);
