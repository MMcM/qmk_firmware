
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   |FNC|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|F13|F14|F15|F16|F17|F18|F19|F20|F21|F22|
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+     +---+---+---+---+---+---+
 *   |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` |BCKSP|     |INS| / |CLR|PRT| BREAK |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] | \ | ^ |     |DEL| * | 7 | 8 | 9 | - |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   |CTL|CAP| A | S | D | F | G | H | J | K | L | ; | ' | RETURN  |     |  UP   | 4 | 5 | 6 | + |
 *   +-------------------------------------------------------------+     +-----------------------+
 *   |  SHIFT  | Z | X | C | V | B | N | M | , | . | / |   SHIFT   |     |LFT|RGT| 1 | 2 | 3 |ENT|
 *   +-------------------------------------------------------------+     +-------------------|   |
 *   |GRPH 1|GRPH 2|                                   | ALT |HELP |     | DOWN  |   0   | . |   |
 *   +-------------+-----------------------------------+-----+-----+     +-------+-------+---+---+
 *
 */
     
  [0] = LAYOUT(
    KC_LALT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRAVE, KC_BSPACE, KC_INS, KC_KP_SLASH, KC_HOME, KC_PSCR, KC_PAUS, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSLASH, KC_NONUS_BSLASH, KC_DEL, KC_KP_ASTERISK, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, \
    KC_LCTRL, KC_LOCKING_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_UP, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS, \
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_LEFT, KC_RIGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, \
    KC_LGUI, KC_RGUI, KC_SPACE, KC_RALT, KC_HELP, KC_DOWN, KC_KP_0, KC_KP_DOT \
    )
} ;
