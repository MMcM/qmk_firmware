
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "timer.h"

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

typedef struct {
    unsigned start_bit:1;
    unsigned code:8;
} queue_entry_t;
#define QUEUE_SIZE 16
static queue_entry_t code_queue[QUEUE_SIZE];
static uint8_t code_queue_in, code_queue_out;

static inline void queue_clear(void) {
    code_queue_in = code_queue_out = 0;
}

static inline bool queue_is_empty(void) {
    return (code_queue_in == code_queue_out);
}

static inline bool queue_is_full(void) {
    // One entry wasted to be able to check this easily.
    return (((code_queue_in + 1) % QUEUE_SIZE) == code_queue_out);
}

static inline queue_entry_t queue_remove(void) {
    queue_entry_t entry = code_queue[code_queue_out];
    code_queue_out = (code_queue_out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(queue_entry_t entry) {
    code_queue[code_queue_in] = entry;
    code_queue_in = (code_queue_in + 1) % QUEUE_SIZE;
}

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define CLOCK_MASK (1 << 0)
#define DATA_MASK (1 << 1)
#define LED_PORT PORTD
#define LED_DDR DDRD
#define LED_MASK (1 << 6)

ISR(INT0_vect) {
    static queue_entry_t fill_entry;
    static int8_t bits_to_go = 0;
    static uint16_t last_start = 0;

    uint8_t data = DATA_PIN;
    uint16_t now_millis = timer_read();
    if (bits_to_go <= 0 || now_millis - last_start > 100) {
        LED_PORT |= LED_MASK;
        fill_entry.start_bit = ((data & DATA_MASK) != 0);
        fill_entry.code = 0;
        bits_to_go = 8;
        last_start = now_millis;
    } else {
        bits_to_go--;
        if ((data & DATA_MASK) != 0) {
            fill_entry.code |= (1 << bits_to_go);
        }
        if (bits_to_go == 0) {
            if (!queue_is_full()) {
                queue_add(fill_entry);
            }
            LED_PORT &= ~LED_MASK;
        }
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    LED_DDR |= LED_MASK;
    LED_PORT &= ~LED_MASK;
    DATA_PORT |= (CLOCK_MASK | DATA_MASK); // Enable pullups
  
    // Interrupt 0 on falling edge of clock.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // There are only break codes for shifts, so must clear all but shifts for anything else.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = (i == 9) ? matrix[i] & 0xF0 : 0x00;
    }

    while (!queue_is_empty()) {
        queue_entry_t entry = queue_remove();
        if (entry.code == 0) continue;
    
        uint8_t col = entry.code & 0x07;
        uint8_t row = (entry.code >> 3) & 0x0F;
    
        if (entry.code & 0x80) {
            matrix[row] &= ~(1 << col);
        } else {
            matrix[row] |= (1 << col);
        }
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse8(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
