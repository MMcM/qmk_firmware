
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+---+   +---+---+---+---+   +---+---+---+---+-----+---+---+---+---+
 * |F1 |F2 |F3 |F4 |   |F5 |F6 |F7 |F8 |   |F9 |F10|F11|F12|     |INS +|DEL -|BRK|
 * +-----------------------------------------------------------------------------+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS  |ALT|PRT| 7 | 8 | 9 |
 * +-----------------------------------------------------------------------------+
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] |   |HLD|NUM| 4 | 5 | 6 |
 * +-----------------------------------------------------|   --------------------+
 * | CTRL | A | S | D | F | G | H | J | K | L | ; | ' |ENTER |UP |HOM| 1 | 2 | 3 |
 * +-----------------------------------------------------------------------------+
 * |CAP|SHFT| Z | X | C | V | B | N | M | , | . | / |SHFT|LFT|DWN|RGT| 0 | . |ENT|
 * +-----------------------------------------------------------------------------+
 *              |                               |
 *              +-------------------------------+
 */
  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, KC_PAUSE, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE, KC_LALT, KC_PSCR, KC_KP_7, KC_KP_8, KC_KP_9, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_SLCK, KC_NLCK, KC_KP_4, KC_KP_5, KC_KP_6, \
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_UP, KC_HOME, KC_KP_1, KC_KP_2, KC_KP_3, \
    KC_CAPS, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_KP_0, KC_KP_DOT, KC_KP_ENTER, \
    KC_SPACE \
  )
} ;
