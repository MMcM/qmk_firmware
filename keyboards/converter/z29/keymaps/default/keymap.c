
#include QMK_KEYBOARD_H
#include "z29_state.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *     |SET|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |HLP|HOM|LFT|UP |RGT|ERS|
 *     +---------------------------------------------------------------+      +---+---+---+---+
 *     |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |DWN|BS |BRK|      | 7 | 8 | 9 | - |
 *     +---------------------------------------------------------------+      +---------------+
 *     | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] | ` |DEL|        | 4 | 5 | 6 | , |
 *    +--------------------------------------------------------------+        +---------------+
 *    |CTL|CAP| A | S | D | F | G | H | J | K | L | ; | ' |RETURN| \ |        | 1 | 2 | 3 |ENT|
 *    +--------------------------------------------------------------+        +-----------+   |
 *    |NSC|SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|LF |           |   0   | . |   |
 *    +---+------+--------------------------------------+-----+---+           +-------+---+---+
 *               |              SPACE                |
 *               +-----------------------------------+
 *
 * Note: CTRL and SHIFT keys are handled specially inside the converter and cannot really be remapped.
 */
     
  [0] = LAYOUT(
    KC_PSCR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_HELP, KC_HOME, KC_LEFT, KC_UP, KC_RIGHT, KC_INSERT, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_DOWN, KC_BSPACE, KC_PAUSE, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_GRAVE, KC_DELETE, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_COMMA, \
    KC_LCTRL, KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_BSLASH, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, \
    KC_SCROLLLOCK, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_PGDOWN, KC_P0, KC_PDOT, \
    KC_SPACE)
} ;

bool led_update_user(led_t led_state) {
  z29_state.offline = led_state.num_lock;
  return true;
}
