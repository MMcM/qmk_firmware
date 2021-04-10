
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

#define SHIFT_PIN PIND
#define SHIFT_PORT PORTD
#define SHIFT_STROBE_MASK (1<<0)
#define SHIFT_MASK (0x1F<<1)
#define CHAR_PIN PINB
#define CHAR_PORT PORTB
#define CHAR_CODE_MASK 0x7F
#define CHAR_BREAK_MASK (1<<7)
#define DSR_PORT PORTC
#define DSR_DDR DDRC
#define DSR_MASK (1<<7)

typedef struct {
    uint8_t shifts;
    uint8_t code;
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
    uint8_t shifts = SHIFT_PIN;
    uint8_t chars = CHAR_PIN;
    queue_entry_t entry;
    entry.shifts = (~shifts & SHIFT_MASK) | (~chars & CHAR_BREAK_MASK);
    entry.code = chars & CHAR_CODE_MASK;
    if (!queue_is_full()) {
        queue_add(entry);
    }
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    SHIFT_PORT |= SHIFT_STROBE_MASK | SHIFT_MASK; // Pullups for strobe and direct reads.

    // Interrupt 0 on rising edge of strobe.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    
    DSR_DDR |= DSR_MASK;        // Output low = turn on.

    matrix_init_quantum();
}

static inline void key_press(uint8_t code) {
    matrix[code >> 4] |= (1 << (code & 0x0F));
}

static void update_shifts(uint8_t shifts) {
    if (shifts & (1 << 1)) {
        key_press(0x53);        // Left shift
    }
    if (shifts & (1 << 2)) {
        key_press(0x3E);        // Caps lock
    }
    if (shifts & (1 << 3)) {
        key_press(0x52);        // Ctrl
    }
    if (shifts & (1 << 4)) {
        key_press(0x13);        // Auto LF
    }
    if (shifts & (1 << 5)) {
        key_press(0x14);        // Local
    }
    if (shifts & (1 << 7)) {
        key_press(0x28);        // Break
    }
}

uint8_t matrix_scan(void) {
    // There are no up transitions; clear initially.
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    if (queue_is_empty()) {
        update_shifts((~SHIFT_PIN & SHIFT_MASK) | (~CHAR_PIN & CHAR_BREAK_MASK));
    } else {
        queue_entry_t entry = queue_remove();
        dprintf("%02X %02X\n", entry.shifts, entry.code);
        update_shifts(entry.shifts);
        key_press(entry.code);
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
