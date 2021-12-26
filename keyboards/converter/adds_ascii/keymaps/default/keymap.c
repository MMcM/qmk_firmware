
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 * +---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
 * |SET| |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|F13|F14|F15|F16| |HOM|CHR|LIN|CLR|
 * +---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
 * +---+    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+
 * |BRK|    |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` |BS |  |Dwn|Lft|Rgt|Up |
 * +---+  +-+-----------------------------------------------------------+  +---------------+
 * |PRT|  |  TAB  | Q | W | E | R | T | Y | U | I | O | P | [ | ] |   |    | 7 | 8 | 9 | - |
 * +---+ ++-------------------------------------------------------|   |    +---------------+
 * |FNC| |DEL|LOCK | A | S | D | F | G | H | J | K | L | ; | ' |RETURN|    | 4 | 5 | 6 | , |
 * +---+ +------------------------------------------------------------+--+ +---------------+
 * |INS| |CTL| SHIFT | Z | X | C | V | B | N | M | , | . | / | SHIFT | \ | | 1 | 2 | 3 |ENT|
 * +---+ +---+-------+-+-----------------------------------+-+-------+---+ +-----------|   |
 *                     |               SPACE               |               |   0   | . |   |
 *                     +-----------------------------------+               +-------+---+---+
 *
 */

  // This layout swaps FUNCT and DEL because the latter sends break codes. One could easily swap the keycaps to match.
  [0] = LAYOUT(
    DEBUG, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_HOME, KC_END, KC_PGUP, KC_PGDN, \
    KC_PAUS, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,                KC_DOWN, KC_LEFT, KC_RIGHT, KC_UP, \
    KC_PSCR, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,                                KC_P7, KC_P8, KC_P9, KC_PMNS, \
    KC_DEL, KC_LALT, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                     KC_P4, KC_P5, KC_P6, KC_PCMM, 
    KC_INS, KC_LCTL, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_BSLS,               KC_P1, KC_P2, KC_P3, KC_PENT, \
    KC_SPACE,                                                                                                                     KC_P0, KC_PDOT \
  )
} ;
