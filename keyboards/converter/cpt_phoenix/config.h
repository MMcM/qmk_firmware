
#pragma once

#define PRODUCT           CPT Phoenix keyboard converter

#define MATRIX_ROWS       8
#define MATRIX_COLS       16

#define SERIAL_UART_BAUD 2400
#define SERIAL_UART_INIT_CUSTOM \
    /* enable TX and RX with interrupt */ \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1) | _BV(RXCIE1); \
    /* 8-bit data */ \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

// Beeper on PC6
#define AUDIO_PIN C6
