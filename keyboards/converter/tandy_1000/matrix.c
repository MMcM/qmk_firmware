
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

#define DATA_PIN PIND
#define DATA_PORT PORTD
#define CLOCK_MASK (1 << 0)
#define DATA_MASK (1 << 1)

typedef struct {
    unsigned sync_lost:1;
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

ISR(INT0_vect) {
    static queue_entry_t entry = { 0, 0 };
    static int8_t shift = 0;

    static unsigned long last_start = 0;
    uint16_t now = timer_read();
    if (shift > 0 && now - last_start > 100) {
        // Start over if taking too long; may have lost a transition.
        entry.sync_lost = 1;
        entry.code = shift = 0;
    }
    if (shift == 0) {
        last_start = now;
    }

    if ((DATA_PIN & DATA_MASK) != 0) {
        entry.code |= (1 << shift); // LSB first.
    }
    shift++;
    if (shift >= 8) {
        if (!queue_is_full()) {
            queue_add(entry);
        }
        entry.sync_lost = entry.code = shift = 0;
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    // Interrupt 0 on rising edge of clock.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // The CAPS and NUM LOCK keys toggle the LED locally and alternately send make and break on each press and nothing on release.
    matrix[0x4] &= ~(1 << 0x5);
    matrix[0x3] &= ~(1 << 0xA);

    while (!queue_is_empty()) {
        queue_entry_t entry = queue_remove();
        dprintf("%s%02X\n", entry.sync_lost ? "?" : "", entry.code);
        uint8_t code = entry.code;

        uint8_t col = code & 0x0F;
        uint8_t row = (code >> 4) & 0x07;
    
        if ((code & 0x80) == 0 || code == 0xC5 || code == 0xBA) {
            // Make or toggle for LOCK key.
            matrix[row] |= (1 << col);
        } else {
            // Break.
            matrix[row] &= ~(1 << col);
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
