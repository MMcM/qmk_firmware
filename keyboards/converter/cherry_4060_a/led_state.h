
#pragma once

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

extern led_state_t led_states[MATRIX_ROWS][MATRIX_COLS];

extern bool update_led_state(led_state_t *p_state);
