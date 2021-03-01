
#pragma once

typedef struct {
    uint8_t row : 4;
    uint8_t col : 4;
} led_matrix_t;

extern const led_matrix_t g_led_matrix[DRIVER_LED_TOTAL];

typedef union {
    uint16_t raw;
    struct {
        uint8_t limit;
        uint8_t threshold;
    };
} led_phase_t;

inline bool phase_is_null(led_phase_t phase) {
    return phase.raw == 0;
}

typedef struct {
    uint8_t set_value;
    uint8_t running_value;
    uint8_t counter;
    led_phase_t phase;
} led_state_t;

extern led_state_t g_led_states[MATRIX_ROWS][MATRIX_COLS];

extern bool update_led_state(led_state_t *p_state);
