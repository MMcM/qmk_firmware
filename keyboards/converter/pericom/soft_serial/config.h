
#pragma once

/* Serial(USART) configuration
 *     asynchronous, negative logic, 1200baud, no flow control
 *     1-start bit, 8-data bit, non parity, 1-stop bit
 */
#define SERIAL_SOFT_BAUD            1200
#define SERIAL_SOFT_PARITY_NONE
#define SERIAL_SOFT_BIT_ORDER_LSB
#define SERIAL_SOFT_LOGIC_NEGATIVE
/* RXD Port */
#define SERIAL_SOFT_RXD_ENABLE
#define SERIAL_SOFT_RXD_DDR         DDRD
#define SERIAL_SOFT_RXD_PORT        PORTD
#define SERIAL_SOFT_RXD_PIN         PIND
#define SERIAL_SOFT_RXD_BIT         2
#define SERIAL_SOFT_RXD_VECT        INT2_vect
/* RXD Interupt */
#define SERIAL_SOFT_RXD_INIT()      do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
    SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
    /* enable interrupt: INT2(rising edge) */ \
    EICRA |= ((1<<ISC21)|(1<<ISC20)); \
    EIMSK |= (1<<INT2); \
    sei(); \
} while (0)
#define SERIAL_SOFT_RXD_INT_ENTER()
#define SERIAL_SOFT_RXD_INT_EXIT()  do { \
    /* clear interrupt  flag */ \
    EIFR = (1<<INTF2); \
} while (0)
#define SERIAL_SOFT_RXD_READ()      (SERIAL_SOFT_RXD_PIN&(1<<SERIAL_SOFT_RXD_BIT))
/* TXD Port */
#define SERIAL_SOFT_TXD_ENABLE
#define SERIAL_SOFT_TXD_DDR         DDRD
#define SERIAL_SOFT_TXD_PORT        PORTD
#define SERIAL_SOFT_TXD_PIN         PIND
#define SERIAL_SOFT_TXD_BIT         3
#define SERIAL_SOFT_TXD_HI()        do { SERIAL_SOFT_TXD_PORT |=  (1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_LO()        do { SERIAL_SOFT_TXD_PORT &= ~(1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_INIT()      do { \
    /* pin configuration: output */ \
    SERIAL_SOFT_TXD_DDR |= (1<<SERIAL_SOFT_TXD_BIT); \
    /* idle */ \
    SERIAL_SOFT_TXD_ON(); \
} while (0)
