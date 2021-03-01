
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"

#include <avr/io.h>

#define DIRECTION_DDR DDRB
#define DIRECTION_PIN PINB
#define DIRECTION_PORT PORTB
#define DIRECTION_FWD (1<<0)
#define DIRECTION_BACK (1<<1)
#define DIRECTION_LEFT (1<<2)
#define DIRECTION_RIGHT (1<<3)
#define DIRECTION_MASK (DIRECTION_FWD|DIRECTION_BACK|DIRECTION_LEFT|DIRECTION_RIGHT)
#define TRIGGER_DDR DDRD
#define TRIGGER_PIN PIND
#define TRIGGER_PORT PORTD
#define TRIGGER_MASK (1<<0)
#define POT_DDR DDRF
#define POT_PIN PINF
#define POT_PORT PORTF
#define POT_A (1<<0)
#define POT_B (1<<1)
#define POT_MASK (POT_A|POT_B)

typedef struct {
    unsigned code:5;
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
    if (!queue_is_full()) {
        queue_entry_t entry;
        entry.code = (DIRECTION_PIN & DIRECTION_MASK);
        if ((POT_PIN & POT_B) != 0) {
            entry.code |= (1 << 4);
        }
        queue_add(entry);
    }
}

void matrix_init_custom(void) {
    // Enable input pull-ups.
    DIRECTION_DDR &= ~DIRECTION_MASK;
    DIRECTION_PORT |= DIRECTION_MASK;
    TRIGGER_DDR &= ~TRIGGER_MASK;
    TRIGGER_PORT |= TRIGGER_MASK;
    POT_DDR &= ~POT_B;
    POT_PORT |= POT_B;

    // Interrupt 0 on falling edge.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    if (!queue_is_empty()) {
        queue_entry_t entry = queue_remove();
        debug_bin8(entry.code);
        dprintln("");
        current_matrix[0] = (1L << entry.code);
        matrix_has_changed = true;
        // Stays low while still pressed.
    } else if (current_matrix[0] != 0 && (TRIGGER_PIN & TRIGGER_MASK) != 0) {
        current_matrix[0] = 0;
        matrix_has_changed = true;
    }

    return matrix_has_changed;
}
