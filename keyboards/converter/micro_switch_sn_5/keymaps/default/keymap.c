
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+
 * |A/C|
 * +---+
 * |PB↑|
 * +---+
 * |S/F|
 * +---+
 * |PB↓|
 * +---+
 * |B/D|
 * +---+
 */
  [0] = LAYOUT(
    KC_A, KC_B, KC_C, KC_D, KC_E
  )
};
