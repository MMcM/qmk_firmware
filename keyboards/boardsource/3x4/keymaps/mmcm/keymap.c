#include QMK_KEYBOARD_H

enum layers {
  _MAIN,
  _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
    KC_P7, KC_P8, KC_P9, KC_P0, 
    KC_P4, KC_P5, KC_P6, KC_PPLS,
    KC_P1, KC_P2, KC_P3, MO(_FN)
  ),
  [_FN] = LAYOUT(
    KC_HOME, KC_UP,   KC_PGUP,  KC_INS,
    KC_LEFT, _______, KC_RIGHT, KC_PENT,
    KC_END,  KC_DOWN, KC_PGDN,  _______
  )
};
