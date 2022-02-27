
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +-----+-----+-----+-----+         +-----+-----+-----+-----+
 *   |UP LF|DN LF|RL UP|RL DN|         |UP   |LEFT |RIGHT|DOWN |
 *  +-----------------------+---+---+--------------------------+
 *  |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |BS | ` |
 *  +-------------------------------------------------------------+
 *  | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] | \ |   |
 * +-------------------------------------------------------------+
 * |CAP|CTL| A | S | D | F | G | H | J | K | L | ; | ' |RETURN |
 * +-----------------------------------------------------------+
 *     |SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|ENT|
 *     +-----+---------------------------------------+-----+---+
 *           |NUM|             SPACE             |BRK|
 *           +---+-------------------------------+---+
 */

  [0] = LAYOUT_standard(
    KC_HOME, KC_END, KC_PGDOWN, KC_PGUP, KC_UP, KC_LEFT, KC_RIGHT, KC_DOWN, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE, KC_GRAVE, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSLASH, KC_DEL, \
    KC_CAPS, KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, \
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_APP, \
    KC_LALT, KC_SPACE, KC_RGUI \
  )
} ;
