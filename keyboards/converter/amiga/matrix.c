
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "wait.h"

static matrix_row_t matrix[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

#define QUEUE_SIZE 16
static uint8_t char_queue[QUEUE_SIZE];
static uint8_t char_queue_in, char_queue_out;

static inline void queue_clear(void) {
    char_queue_in = char_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (char_queue_in == char_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((char_queue_in + 1) % QUEUE_SIZE) == char_queue_out);
}

static inline uint8_t queue_remove(void) {
    uint8_t code = char_queue[char_queue_out];
    char_queue_out = (char_queue_out + 1) % QUEUE_SIZE;
    return code;
}

static inline void queue_add(uint8_t code) {
    char_queue[char_queue_in] = code;
    char_queue_in = (char_queue_in + 1) % QUEUE_SIZE;
}

#define DATA_PORT PORTD
#define DATA_DDR DDRD
#define DATA_PIN PIND
#define DATA_MASK (1 << 0)
#define CLOCK_MASK (1 << 1)
#define LED_PORT PORTD
#define LED_DDR DDRD
#define LED_MASK (1 << 6)

#ifndef NEED_RESYNC
#define NEED_RESYNC 1
#endif

#if NEED_RESYNC
static uint16_t timer_high = 0;

static inline uint32_t read_timer(void) {
    return ((uint32_t)timer_high << 16) | (uint32_t)TCNT3;
}

SIGNAL(TIMER3_OVF_vect) {
    timer_high++;
}
#endif

ISR(INT1_vect) {
    static uint8_t nbits = 0;
    static uint8_t fill_code;
    static unsigned long last_bit = 0;

    uint8_t data = DATA_PIN;
#if NEED_RESYNC
    unsigned long now = read_timer();
    if (now - last_bit > 16) {
        // The documentation describes a out-of-sync protocol from the keyboard side, but it does
        // not seem to always be present. So if it's been more than 64us since the last clock assume
        // we have started over.
        // TODO: Will this confuse resync if it is present?
        nbits = 0;
    }
    last_bit = now;
#endif
    if (nbits == 0) {
        fill_code = 0;
        LED_PORT |= LED_MASK;
    }
    if ((data & DATA_MASK) == 0) {
        fill_code |= (1 << (nbits == 7 ? 7 : 6 - nbits));
    }
    nbits++;
    if (nbits >= 8) {
        while ((DATA_PIN & (DATA_MASK | CLOCK_MASK)) != (DATA_MASK | CLOCK_MASK));
        wait_us(10);
        LED_PORT &= ~LED_MASK;
        DATA_DDR |= DATA_MASK;
        DATA_PORT &= ~DATA_MASK;
        if (!queue_is_full()) {
            queue_add(fill_code);
        }
        wait_us(85);
        DATA_PORT |= DATA_MASK;
        DATA_DDR &= ~DATA_MASK;
        nbits = 0;
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    LED_DDR |= LED_MASK;
    LED_PORT &= ~LED_MASK;
    DATA_PORT |= (CLOCK_MASK | DATA_MASK); // Enable pullups
  
    // Interrupt 1 on falling edge of clock.
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);

#if NEED_RESYNC
    // Configure TCNT3 to count once every 4us.
    TCCR3A = 0;                     // Normal
    TCCR3B = _BV(CS31) | _BV(CS30); // Prescalar = 64
    TIMSK3 |= _BV(TOIE3);           // Enable overflow interrupt
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    if (!queue_is_empty()) {
        uint8_t code = queue_remove();

        dprintf("%02X\n", code);

        uint8_t col = code & 0x0F;
        uint8_t row = (code >> 4) & 0x07;
        if (row > 6) {
          switch (code) {
          case 0x78:
            // Reset warning
            break;
          case 0xF9:
            // Last key bad
            break;
          case 0xFA:
            // Keyboard output buffer overflow
            break;
          case 0xFC:
            // Keyboard selftest failed
            break;
          case 0xFD:
            // Initiate power-up key stream (keys pressed at powerup)
            break;
          case 0xFE:
            // Terminate power-up key stream
            break;
          }
        } else if ((code & 0x80) != 0) {
          matrix[row] &= ~(1 << col);
        } else {
          matrix[row] |= (1 << col);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
