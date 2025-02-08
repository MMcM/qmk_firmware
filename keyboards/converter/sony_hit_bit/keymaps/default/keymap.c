
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+      | \-------/ |
 * |F1 F6|F2 F7|F3 F8|F4 F9|F5F10|     |HOME | INS | DEL |STOP |      |  \     /  |
 * +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+      |   >---<   |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+      |  /     \  |
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ¥ |BS |      | /-------\ |
 * +-----------------------------------------------------------+   +---------------+
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | @ | [ |     |   | 7 | 8 | 9 | / |
 * +-----------------------------------------------------|RETRN|   +---------------+
 * | CTRL | A | S | D | F | G | H | J | K | L | ; | : | ] |    |   | 4 | 5 | 6 | * |
 * +-----------------------------------------------------------+   +---------------+
 * | SHIFT  | Z | X | C | V | B | N | M | , | . | / | _ |SHIFT |   | 1 | 2 | 3 | - |
 * +----+---------------------------------------------------+--+   +---------------+
 *      | CAP |GRP|             SPACE             |KANA |SEL|      | 0 | . | , | + |
 *      +-----+---+-------------------------------+-----+---+      +---+---+---+---+
 */

  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_HOME, KC_INS, KC_DEL, KC_PAUS, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, JP_YEN, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LBRC, KC_ENT,       KC_P7, KC_P8, KC_P9, KC_PSLS,
    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC,          KC_P4, KC_P5, KC_P6, KC_PAST,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, JP_BSLS, /*KC_RSFT,*/ KC_P1, KC_P2, KC_P3, KC_PMNS,
    KC_CAPS, KC_LALT, KC_SPACE, JP_KANA, KC_RGUI,                                                      KC_P0, KC_PDOT, KC_PCMM, KC_PPLS)
} ;
