
#include QMK_KEYBOARD_H

enum layers {
    BASE,
    GRAPH,
    TV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +----+  +---+
 * |テレビ|  |電源|
 * +----+  +---+
 *
 * +---+---+-------+-------+-------+-------+-------+---+---+-----+
 * |STP|MOD|  F1   |  F2   |  F3   |  F4   |  F5   |CLR|PAG|DEL  |
 * +-------------------------------------------------------------+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ¥ |INS  |
 * +-------------------------------------------------------------+
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | @ | [ | ] |   |
 * +---------------------------------------------------------|   |
 * | CTRL | A | S | D | F | G | H | J | K | L | ; | : | ー |RETURN|
 * +-------------------------------------------------------------+
 * |  SHIFT | Z | X | C | V | B | N | M | , | . | / |SHFT| ↑ |かな|
 * +-------------------------------------------------------------+
 * |CAP|GPH|                SPACE                    | ← | ↓ | → |
 * +---+---+-----------------------------------------+---+---+---+
 */

  [BASE] = LAYOUT(
    MO(TV), QK_BOOT,
    KC_LGUI, KC_PSCR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_HOME, KC_PGDN, KC_BSPC,
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_INS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LBRC, KC_RBRC,
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUBS, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_KANA,
    KC_CAPS, MO(GRAPH), KC_SPACE, KC_LEFT, KC_DOWN, KC_RIGHT
  ),

  // Note that ones not assigned here aren't possible due to the lossy encoding.

  [GRAPH] = LAYOUT(
    KC_NO, KC_TRNS,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5), A(KC_6), A(KC_7), A(KC_8), A(KC_9), A(KC_0), A(KC_MINS), KC_NO, A(KC_JYEN), KC_NO,
    KC_NO, KC_NO, KC_NO, A(KC_E), A(KC_R), A(KC_T), A(KC_Y), A(KC_U), A(KC_I), A(KC_O), A(KC_P), A(KC_GRV), A(KC_LBRC), A(KC_RBRC),
    KC_NO, KC_NO, A(KC_S), A(KC_D), A(KC_F), A(KC_G), A(KC_H), A(KC_J), A(KC_K), A(KC_L), A(KC_SCLN), A(KC_QUOT), A(KC_NUBS), KC_NO,
    KC_NO, KC_NO, A(KC_X), A(KC_C), A(KC_V), A(KC_B), A(KC_N), A(KC_M), A(KC_COMM), A(KC_DOT), A(KC_SLSH), KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  ),

  [TV] = LAYOUT(
    KC_TRNS, KC_NO,
    KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_MSTP, KC_EJCT,
    KC_NO, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  )
} ;
