
#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NUMERIC,
    ALPHA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/**
 * +----+---+---+---+---+---+---+---+---+---+---+---+---+
 * |HEX |@#`|%'[|*$||<·]|VCR|INS|-_~|/ 0|FLD|CMD|BYP|CHR|
 * +----------------------------------------------------+
 * |   |Q +|W −|E )| R |T \| Y |U 1|I 2|O 3|P &|REC|FREL|
 * +   |-------------------------------------------|    |
 * |RST | A |S >|D :| F | G |H '|J 4|K 5|L 6|DEL|AUT|   |
 * +----------------------------------------------------+
 * |NUMERC| Z |X ?|C "|V =|B !|N (|M 7|,{8|.}9|   |ALPHA|
 * +----------------------------------------------------+
 * |REPT |                                   |REPT |LCA |
 * +-----+-----------------------------------+-----+----+
 */

  [BASE] = LAYOUT(
    KC_LALT, KC_AT, KC_PERC, KC_ASTR, KC_LABK, KC_F1, KC_INS, KC_MINS, KC_SLSH, KC_TAB, KC_ESC, KC_PSCR, KC_BSPC,
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_PGUP, KC_ENT,
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_DEL, KC_HOME,
    MO(NUMERIC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_CAPS, MO(ALPHA),
    KC_NO, KC_SPACE, KC_NO, KC_RGUI
  ),
  [NUMERIC] = LAYOUT(
    _______, KC_HASH, KC_QUOT, KC_DLR, KC_DOT, KC_F2, KC_F3, KC_UNDS, KC_0, KC_LEFT, KC_F4, KC_F5, KC_DEL,
    KC_PLUS, KC_MINS, KC_RPRN, KC_NO, KC_BSLS, KC_NO, KC_1, KC_2, KC_3, KC_AMPR, KC_PGDN, _______,
    _______, KC_NO, KC_RABK, KC_COLN, KC_SCLN, KC_GRV, KC_QUOT, KC_4, KC_5, KC_6, _______, KC_END,
    _______, KC_NO, KC_QUES, KC_DQUO, KC_EQL, KC_EXLM, KC_LPRN, KC_7, KC_8, KC_9, _______, _______,
    _______, _______, _______, _______
  ),
  [ALPHA] = LAYOUT(
    _______, KC_CIRC, KC_LBRC, KC_PIPE, KC_RBRC, KC_F6, KC_F7, KC_TILD, KC_NO, KC_RGHT, KC_F8, KC_F9, KC_DEL,
    S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_PGDN, _______,
    _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), _______, KC_END,
    _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), KC_LCBR, KC_RCBR, _______, _______,
    _______, _______, _______, _______
  )
} ;
