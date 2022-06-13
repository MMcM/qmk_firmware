
#pragma once

#include "config_common.h"

#define PRODUCT           Alphameric Type 140 keyboard converter
                          
#define MATRIX_ROWS       8
#define MATRIX_COLS       16

// Compatible with Soarer's
#define XT_CLOCK_PORT  PORTD
#define XT_CLOCK_PIN   PIND
#define XT_CLOCK_DDR   DDRD
#define XT_CLOCK_BIT   1
#define XT_DATA_PORT   PORTD
#define XT_DATA_PIN    PIND
#define XT_DATA_DDR    DDRD
#define XT_DATA_BIT    0
#define XT_RST_PORT    PORTB
#define XT_RST_PIN     PINB
#define XT_RST_DDR     DDRB
#define XT_RST_BIT     7

// Hard reset
#define XT_RESET() do { \
    XT_RST_PORT &= ~(1<<XT_RST_BIT);  \
    XT_RST_DDR  |=  (1<<XT_RST_BIT);  \
    _delay_ms(500);                   \
    XT_RST_DDR  &= ~(1<<XT_RST_BIT);  \
} while (0)

#define XT_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)

#define XT_INT_ON()  do {      \
    EIFR  |= (1<<INTF1);        \
    EIMSK |= (1<<INT1);         \
} while (0)

#define XT_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)

#define XT_INT_VECT    INT1_vect
