
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+  +-------+-------+-------+-------+-------+  +---+---+
 * |STP|CPY|  |  f·1  |  f·2  |  f·3  |  f·4  |  f·5  |  |RUP|RDN|
 * +---+---+  +-------+-------+-------+-------+-------+  +---+---+
 * +----+---+---+---+---+---+---+---+---+---+---+---+---+---+----+      +---+---+---+---+
 * |ESC | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ¥ |DEL |      |HOM|HLP| - | / |
 * +-------------------------------------------------------------+      +---------------+
 * | TAB  | Q | W | E | R | T | Y | U | I | O | P | @ | [ | RET  |      | 7 | 8 | 9 | * |
 * +-------------------------------------------------------|     |      +---------------+
 * |CTL|CAP| A | S | D | F | G | H | J | K | L | ; | : | ] |     |      | 4 | 5 | 6 | + |
 * +-------------------------------------------------------------+---+  +---------------+
 * |  SHIFT  | Z | X | C | V | B | N | M | , | . | / |   | SHIFT |UP |  | 1 | 2 | 3 | = |
 * +---------+-------------------------------------------+-----------+  +---------------+
 *           |KAN|GPH|             SPACE             |   |LFT|RGT|DWN|  | 0 | , | . |RET|
 *           +---+---+-------------------------------+   +---+---+---+  +---+---+---+---+
 * 
 */

  [0] = LAYOUT_8801(
    KC_PAUS, KC_COPY, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_PGUP, KC_PGDN,
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC, KC_HOME, KC_HELP, KC_PMNS, KC_PSLS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LBRC, KC_ENT,           KC_P7, KC_P8, KC_P9, KC_PAST,
    KC_LCTL, KC_LCAP, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC,     KC_P4, KC_P5, KC_P6, KC_PPLS,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_RSFT, KC_UP,    KC_P1, KC_P2, KC_P3, KC_PEQL,
    KC_KANA, KC_LALT, KC_SPACE, KC_LEFT, KC_RGHT, KC_DOWN,                                                 KC_P0, KC_PCMM, KC_PDOT, KC_PENT)
} ;
