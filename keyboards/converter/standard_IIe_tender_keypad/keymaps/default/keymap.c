
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *     +---+---+---+---+   +---+---+
 *     |DEL| * | / | + |   |ESC| ? |
 *     +---------------+   +-------+
 *     | 7 | 8 | 9 | , |   | ( | ) |
 *     +---------------+   +-------+
 *     | 4 | 5 | 6 | - |   |DWN|UP |
 *     +---------------+   +-------+
 *     | 1 | 2 | 3 |ENT|   |LFT|RGT|
 *     +-----------|   |   +-------+
 *     |   0   | . |   |   | SPACE |
 *     +---------------+   +-------+
 *
 */
     
  [0] = LAYOUT(
    KC_DEL, KC_KP_ASTERISK, KC_KP_SLASH, KC_KP_PLUS, KC_ESC, KC_KP_EQUAL, \
    KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_COMMA, KC_LBRACKET, KC_RBRACKET, \
    KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS, KC_DOWN, KC_UP, \
    KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_LEFT, KC_RIGHT, \
    KC_KP_0, KC_KP_DOT, KC_SPACE)
};
