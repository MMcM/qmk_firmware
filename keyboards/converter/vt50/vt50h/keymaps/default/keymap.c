
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---------------+
 *     |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` |BS |BRK|   |   |   |   |UP |
 *     +---------------------------------------------------------------+   +---------------+
 *     | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | \ |LF |DEL|     | 7 | 8 | 9 |DWN|
 *    +----------------------------------------------------------------+   +---------------+
 *    |CTL|CAP| A | S | D | F | G | H | J | K | L | ; | ' | { | RETURN |   | 4 | 5 | 6 |RGT|
 *    +----------------------------------------------------------------+   +---------------+
 *    |SCL|SHIFT| Z | X | C | V | B | N | M | , | . | / |SHIFT|RPT|COP|    | 1 | 2 | 3 |LFT|
 *    +---+-----+---------------------------------------+-----+---+---+    +-----------+---|
 *                 |              SPACE               |                    |   0   | . |ENT|
 *                 +----------------------------------+                    +-------+---+---+
 *
 */

    [0] = LAYOUT(
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, KC_PAUS, KC_F1, KC_F2, KC_F3, KC_UP, \
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_BSLS, KC_INS, KC_DEL, KC_P7, KC_P8, KC_P9, KC_DOWN, \
  KC_LCTL, KC_LCAP, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC, KC_ENT, KC_P4, KC_P5, KC_P6, KC_RGHT, \
  KC_LALT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RGUI, KC_RALT, KC_P1, KC_P2, KC_P3, KC_LEFT,  \
  KC_SPC, KC_P0, KC_PDOT, KC_PENT \
    )
} ;
