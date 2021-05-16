
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +-----+---+---+---+---+---+---+  +---+---+---+---+---+---+----+  +---+---+---+  +---+---+---+---+
 * |     |F1 |F2 |F3 |F4 |F5 |F6 |  |F7 |F8 |F9 |F10|F11|F12|    |  |   |   |   |  |   |   |   |   |
 * +-----+---+---+---+---+---+---+  +---+---+---+---+---+---+----+  +---+---+---+  +---+---+---+---+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+  +---+---+---+  +---+---+---+---+
 * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Esc|Bspce|  |   |   |   |  |Rst||<-|LF |Xmt|
 * +-------------------------------------------------------------+  +-----------+  +---------------+
 * | Tab | Q | W | E | R | T | Y | U | I | O | P | \ |[ ]|   |   |  |Ins|Ers|Del|  | 7 | 8 | 9 |->||
 * +-------------------------------------------------------------|  +---+---+---+  +---------------+
 * |Lock  | A | S | D | F | G | H | J | K | L | ; | ' |{ }|Return|      | U |      | 4 | 5 | 6 |CR |
 * +-------------------------------------------------------------+  +---+---+---+  +---------------+
 * | Shift  | Z | X | C | V | B | N | M | , | . | / | Shift  |   |  | L |Hom| R |  | 1 | 2 | 3 | + |
 * +--------+---------------------------------------+-----------++  +---+---+---+  +---------------|
 *          |     |                           |     |     |Cntrl|       | D |      | , | 0 | . | - |
 *          +-----+---------------------------+-----+     +-----+       +---+      +-------+---+---+
 */

  [0] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_PSCR, KC_SLCK, KC_PAUS, KC_NLCK, KC_LCAP, KC_LNUM, KC_LSCR, \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_ESC, KC_BSPC, KC_PGUP, KC_END, KC_PGDN, KC_STOP, KC_BSPC, KC_EXEC, KC_PSLS, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_LBRC, KC_NO, KC_NO, KC_INS, KC_CUT, KC_DEL, KC_P7, KC_P8, KC_P9, KC_PAST, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC, KC_ENT, KC_UP, KC_P4, KC_P5, KC_P6, KC_PENT, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_APP, KC_LEFT, KC_HOME, KC_RIGHT, KC_P1, KC_P2, KC_P3, KC_PPLS, \
    KC_NO, KC_SPACE, KC_NO, KC_RCTL, KC_DOWN, KC_PCMM, KC_P0, KC_PDOT, KC_PMNS \
  )
} ;
