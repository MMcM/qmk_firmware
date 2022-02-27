
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+                                                             +-----+---+-----+
 * |NXP|SUP|                                                             |MARK |UP |BOUND|
 * +---+---+  +----+----+----+  +----+----+----+----+  +----+----+----+  +-----+---+-----+
 * |PRV|SDN|  | f1 | f2 | f3 |  | f4 | f5 | f6 | f7 |  | f8 | f9 |f10 |  |LEFT |DWN|RIGHT|
 * +---+---+  +----+----+----+  +----+----+----+----+  +----+----+----+  +-----+---+-----+
 * +---+---+  +-------------------------------------------------------+  +---------------+
 * |CNL|MOV|  | ^ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |BS |  | 7 | 8 | 9 |GO |
 * +-------+  +-------------------------------------------------------+  +---------------+
 * |HLP|DEL|  |TAB| Q | W | E | R | T | Y | U | I | O | P |1/2| [ | ] |  | 4 | 5 | 6 | - |
 * +-------+  +-------------------------------------------------------+  +---------------+
 * |ACT|OVR|  |LOCK | A | S | D | F | G | H | J | K | L | ; | ' | RET |  | 1 | 2 | 3 |NXT|
 * +-------+  +-------------------------------------------------------+  +-----------+   |
 * |FIN|COP|  | SHIFT | Z | X | C | V | B | N | M | , | . | / | SHIFT |  |   0   | . |   |
 * +-------+  +-------+---------------------------------------+-------+  +-------+---+---+
 *                       |CODE|        SPACE          |CODE|
 *                       +----+-----------------------+----+
 *
 */
     
  [0] = LAYOUT_k1(
    KC_END, KC_PGUP, KC_PSCR, KC_UP, KC_PAUS, \
    KC_HOME, KC_PGDN, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_LEFT, KC_DOWN, KC_RIGHT, \
    KC_ESC, KC_COPY, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_P7, KC_P8, KC_P9, KC_EXEC, \
    KC_HELP, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_F11, KC_LBRC, KC_RBRC, KC_P4, KC_P5, KC_P6, KC_PMNS, \
    KC_MENU, KC_INS, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P1, KC_P2, KC_P3, KC_PENT, \
    KC_APP, KC_LALT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_P0, KC_PDOT, \
    KC_LCTL, KC_SPC, KC_RCTL \
  )
} ;
