
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+------+-------+-------+
 * |F1 |F2 | |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |  BS  |NUM LCK|SCR LCK|
 * +-------+ +--------------------------------------------------------------------------+
 * |F3 |F4 | | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ]  |   | 7 | 8 | 9 | - |
 * +-------+ +------------------------------------------------------|ENT|---------------+
 * |F5 |F6 | | CTRL | A | S | D | F | G | H | J | K | L | ; | ' | ` |   | 4 | 5 | 6 |   |
 * +-------+ +----------------------------------------------------------------------|   |
 * |F7 |F8 | |SHFT| \ | Z | X | C | V | B | N | M | , | . | / |SHFT |PRT| 1 | 2 | 3 | + |
 * +-------+ +----------------------------------------------------------------------|   |
 * |F9 |F10| |  ALT  |                SPACE                |CAPS LCK|   0   |   .   |   |
 * +---+---+ +-------+-------------------------------------+--------+-------+-------+---+
 * 
 */

  [0] = LAYOUT_xt(
    KC_F1, KC_F2,  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NLCK, KC_SLCK,
    KC_F3, KC_F4,  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENTER, KC_P7, KC_P8, KC_P9, KC_PMNS,
    KC_F5, KC_F6,  KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_GRV, KC_P4, KC_P5, KC_P6, KC_PPLS,
    KC_F7, KC_F8,  KC_LSFT, KC_BSLS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_PSCR, KC_P1, KC_P2, KC_P3,
    KC_F9, KC_F10, KC_LALT, KC_SPACE, KC_CAPS, KC_P0, KC_PDOT
  )
} ;
