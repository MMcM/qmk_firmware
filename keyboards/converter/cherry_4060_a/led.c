
#include <stdint.h>
#include <stdbool.h>

#include "debug.h"
#include "print.h"
#include "quantum.h"

#ifdef LED_MATRIX_ENABLE

#include "led_matrix.h"

#include "led_state.h"

typedef struct {
    uint8_t value;
    led_phase_t phase;
} led_mode_t;

#define LED_MODE(v, l, t) { .value = v, .phase = { .limit = l, .threshold = t } }

// The scan / update frequency for any row is 9600 / 10 / 8 = 120Hz.
// Only set those with period less than .1s so while maybe flickering it isn't flashing.
static const led_mode_t PROGMEM led_modes[] = {
    LED_MODE(0, 0, 0),
    LED_MODE(10, 12, 10),
    LED_MODE(12, 10, 8),
    LED_MODE(15, 8, 6),
    LED_MODE(20, 6, 4),
    LED_MODE(24, 5, 3),
    LED_MODE(30, 4, 2),
    LED_MODE(36, 10, 6),
    LED_MODE(40, 3, 1),
    LED_MODE(45, 8, 4),
    LED_MODE(48, 5, 2),
    LED_MODE(50, 12, 6),
    LED_MODE(60, 2, 0),
    LED_MODE(70, 12, 4),
    LED_MODE(72, 5, 1),
    LED_MODE(75, 8, 2),
    LED_MODE(80, 3, 0),
    LED_MODE(84, 10, 2),
    LED_MODE(90, 4, 0),
    LED_MODE(96, 5, 0),
    LED_MODE(100, 6, 0),
    LED_MODE(105, 8, 0),
    LED_MODE(108, 10, 0),
    LED_MODE(110, 12, 0),
    LED_MODE(120, 0, 0)
};

static led_phase_t init_state_for_nearest_mode(uint8_t value) {
    led_phase_t phase;
    if (value == 0 || value >= 120) {
        phase.raw = 0;
        return phase;
    }
    uint8_t lo = 0;
    uint8_t hi = sizeof(led_modes)/sizeof(led_modes[0])-1;
    while (true) {
        uint8_t mid = (lo + hi + 1) / 2;
        const led_mode_t *p_mode = led_modes + mid;
        uint8_t mode_value = pgm_read_byte(&p_mode->value);
        if (mid == hi || mode_value == value) {
            phase.raw = pgm_read_word(&p_mode->phase.raw);
            return phase;
        }
        if (mode_value < value) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
}

static void set_value(int index, uint8_t value) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        led_matrix_t led_matrix = g_led_matrix[index];
        g_led_states[led_matrix.row][led_matrix.col].set_value = value;
    }
}

static void set_value_all(uint8_t value) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        led_state_t *states = g_led_states[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            states[col].set_value = value;
        }
    }
}

static void init(void) {
    set_value_all(0);
}

static void flush(void) {
}

const led_matrix_driver_t led_matrix_driver = {
    .init  = init,
    .set_value = set_value,
    .set_value_all = set_value_all,
    .flush = flush
};

led_state_t g_led_states[MATRIX_ROWS][MATRIX_COLS];

bool update_led_state(led_state_t *p_state) {
    if (p_state->running_value != p_state->set_value) {
        p_state->running_value = p_state->set_value;
        led_phase_t phase = init_state_for_nearest_mode(p_state->running_value);
        if (p_state->phase.raw != phase.raw) {
            p_state->phase.raw = phase.raw;
            if (phase_is_null(phase) && p_state->running_value > 0) {
                p_state->counter = 1;   // Always on.
            } else {
                p_state->counter = 0;   // Start over (or always off).
            }
        }
    }  
    if (!phase_is_null(p_state->phase)) {
        uint8_t counter = p_state->counter + 1;
        if (counter >= p_state->phase.limit) {
            counter = 0;
        }
        p_state->counter = counter;
    }
    return p_state->counter > p_state->phase.threshold;
}

#endif
