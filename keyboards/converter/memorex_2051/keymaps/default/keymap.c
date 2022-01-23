
#include QMK_KEYBOARD_H

enum user_keycodes {
    RBRC_OR_PDOT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+   +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+-----------+---+
 * |SYS|CMD|   | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS  |   BTAB    |DUP|
 * +-------+   +-------------------------------------------------------------------------+
 * |DEL|ERS|   |TAB  | Q | W | E | R | T | Y | U | I | O | P | ¢ | \ |FEX| 7 | 8 | 9 |FL-|
 * +-------+   +-----------------------------------------------------|   ----------------+
 * |PRT|HLP|   |CTRL | A | S | D | F | G | H | J | K | L | ; | ' | { |   | 4 | 5 | 6 |FL+|
 * +-------+   +---------------------------------------------------------------------|   |
 * |UP |DWN|   |SHFT|<> | Z | X | C | V | B | N | M | , | . | / |SHFT|RET| 1 | 2 | 3 |   |
 * +-------+   +---------------------------------------------------------------------|   |
 * |LFT|RGT|   |ERR RESET|              SPACE                | ENTER |     0     | . |   |
 * +---+---+   +---------+-----------------------------------+-------+-----------+---+---+
 */

  [0] = LAYOUT(
    KC_PAUS, KC_ESC,   KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NUM, KC_PAST,
    KC_DEL,  KC_INS,   KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_BSLS, KC_ENT, KC_P7, KC_P8, KC_P9, KC_PMNS,
    KC_PSCR, KC_HELP,  KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_RBRC, KC_P4, KC_P5, KC_P6, KC_PPLS,
    KC_UP,   KC_DOWN,  KC_LSFT, KC_NUHS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_RETN, KC_P1, KC_P2, KC_P3,
    KC_LEFT, KC_RGHT,  KC_APP, KC_SPACE, KC_MENU, KC_P0, KC_PDOT
  )
} ;
