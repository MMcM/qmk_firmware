
#pragma once
                          
#define MATRIX_ROWS       24
#define MATRIX_COLS       32

/*
 * PS/2 USART configuration for ATMega32U4
 */
#ifdef PS2_DRIVER_USART
#error The UART is needed for the mouse; use PS2_DRIVER=interrupt.
#endif


/*
 * PS/2 Interrupt configuration
 */
#ifdef PS2_DRIVER_INTERRUPT
/* uses INT1 for clock line(ATMega32U4) */
#define PS2_CLOCK_PIN   D1
#define PS2_DATA_PIN    D0

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT1);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define PS2_INT_VECT    INT1_vect
#endif


/*
 * PS/2 Busywait configuration
 */
#ifdef PS2_DRIVER_BUSYWAIT
#define PS2_CLOCK_PIN   D1
#define PS2_DATA_PIN    D0
#endif
