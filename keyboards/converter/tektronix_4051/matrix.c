
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

typedef struct {
    unsigned key_state:1;
    unsigned key_number:7;
} queue_entry_t;

#define QUEUE_SIZE 4
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

#define KEY_PIN PIND
#define KEY_PORT PORTD
#define KEY_MASK (1 << 3)

#define KBHALT_DDR DDRC
#define KBHALT_PORT PORTC
#define KBHALT_MASK (1 << 6)

#define KBCLK_DDR DDRC
#define KBCLK_PORT PORTC
#define KBCLK_MASK (1 << 7)

#define KC_PIN PINB
#define KC_MASK 0x7F

#define DIRECT_PIN PINF
#define DIRECT_PORT PORTF
#define DIRECT_SHIFT_MASK (1 << 5)
#define DIRECT_CTRL_MASK (1 << 6)
#define DIRECT_TTY_MASK (1 << 7)

#ifndef KBCLK_TIMER
// It is too hard to get everything copied before a reasonably short clock cycle.
// Can manage the same 2us for most of the scan inline instead.
#define KBCLK_TIMER 0
#endif

ISR(INT3_vect) {
    KBHALT_PORT |= KBHALT_MASK;
    queue_entry_t key_change;
    key_change.key_state = (KEY_PIN & KEY_MASK) != 0;
    key_change.key_number = KC_PIN & KC_MASK;
    if (queue_is_full()) {
        KBHALT_PORT &= ~KBHALT_MASK;
    } else {
        queue_add(key_change);
    }
}

#define ROW(code) (code >> 4)
#define COL(code) (code & 0x0F)

// Need these on separate rows to avoid anti-ghosting.
#define DIRECT_SHIFT_KEY (8 * MATRIX_COLS)
#define DIRECT_CTRL_KEY (9 * MATRIX_COLS)
#define DIRECT_TTY_KEY (10 * MATRIX_COLS)

inline static bool matrix_make(matrix_row_t matrix[], uint8_t code) {
    uint8_t row = ROW(code);
    uint8_t col = COL(code);
    uint16_t mask = (uint16_t)1 << col;
    if ((matrix[row] & mask) == 0) {
        matrix[row] |= mask;
        return true;
    }
    return false;
}

inline static bool matrix_break(matrix_row_t matrix[], uint8_t code) {
    uint8_t row = ROW(code);
    uint8_t col = COL(code);
    uint16_t mask = (uint16_t)1 << col;
    if ((matrix[row] & mask) != 0) {
        matrix[row] &= ~mask;
        return true;
    }
    return false;
}

inline static bool matrix_set(matrix_row_t matrix[], uint8_t code, bool state) {
    if (state) {
        return matrix_make(matrix, code);
    } else {
        return matrix_break(matrix, code);
    }
}

inline static void matrix_clear(matrix_row_t matrix[]) {
    // Only clear the part managed by the scan, not the direct shifts.
    for (uint8_t i = 0; i < REAL_MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

static bool handle_key_change(matrix_row_t matrix[], queue_entry_t key_change) {
    bool key_state = key_change.key_state;
    uint8_t key_number = key_change.key_number;
    static bool any_key_down = false;
    if (key_state == false) {   // Falling
        if (!any_key_down) {
            any_key_down = true;
        }
        return false;
    }
    static uint8_t last_key_number = 0xFF;
    if (key_number == 0) {
        // Last key up.
        matrix_clear(matrix);
        any_key_down = false;
        last_key_number = 0xFF;
        return true;
    }
    bool changed = false;
    if (last_key_number != 0xFF) {
        for (uint8_t key = (last_key_number + 1) & 0x7F; key != key_number; key = (key + 1) & 0x7F) {
            changed |= matrix_break(matrix, key);
        }
    }
    changed |= matrix_make(matrix, key_number);
    last_key_number = key_number;
    return changed;
}

void matrix_init_custom(void) {
    KEY_PORT |= KEY_MASK;
    KBCLK_DDR |= KBCLK_MASK;
    KBHALT_DDR |= KBHALT_MASK;

    DIRECT_PORT |= (DIRECT_SHIFT_MASK | DIRECT_CTRL_MASK | DIRECT_TTY_MASK);

#if KBCLK_TIMER
    // Timer4 PWM every 2us with 25% duty cycle.
    TC4H = 0;
    OCR4C = 0x10;
    TCCR4A = _BV(COM4A1) | _BV(PWM4A);
    TCCR4B = _BV(CS40);
    TC4H = 0;
    OCR4A = 0x04;
#endif

    // Interrupt 3 on either edge.
    EICRA |= _BV(ISC30);
    EIMSK |= _BV(INT3);

    wait_us(1);
    queue_clear();
    KBHALT_PORT &= ~KBHALT_MASK;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
#if 0
    debug_enable = true;
    debug_matrix = true;
#endif

#if !KBCLK_TIMER
    for (uint8_t i = 0; i < 128; i++) {
        KBCLK_PORT |= KBCLK_MASK;
        asm("nop");
        KBCLK_PORT &= ~KBCLK_MASK;
        wait_us(1);
        if (!queue_is_empty()) {
            break;
        }
    }
#endif

    bool changed = false;

    if (!queue_is_empty()) {
        do {
            queue_entry_t entry = queue_remove();
            changed |= handle_key_change(current_matrix, entry);
        } while (!queue_is_empty());
        KBHALT_PORT &= ~KBHALT_MASK;
    }

    uint8_t direct = DIRECT_PIN;
    changed |= matrix_set(current_matrix, DIRECT_SHIFT_KEY, (direct & DIRECT_SHIFT_MASK) == 0);
    changed |= matrix_set(current_matrix, DIRECT_CTRL_KEY, (direct & DIRECT_CTRL_MASK) == 0);
    changed |= matrix_set(current_matrix, DIRECT_TTY_KEY, (direct & DIRECT_TTY_MASK) == 0);

    return changed;
}
