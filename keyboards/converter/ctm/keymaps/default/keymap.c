
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 * +---+---+---+---+      +---+---+---+---+     +---+---+---+---+  +---+---+---+  +---+---+---+---+---+
 * |F1 |F2 |F3 |F4 |      |F5 |F6 |F7 |F8 |     |F9 |F10|F11|F12|  |FUN|HLP|END|  |SYS|CLR|STR|   |   |
 * +---+---+---+---+      +---+---+---+---+     +---+---+---+---+  +---+---+---+  +---+---+---+---+---+
 * +----+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+  +---+---+---+---+---+
 * |< > | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 |, ?|^ `|<x||RUN|  |PRV|PUP|HOM|  | # | 7 | 8 | 9 | * |
 * +------------------------------------------------------------+  +-----------+  +-------------------+
 * | TAB  | Q | W | E | R | T | Z | U | I | O | P |ü è|¨ ' ~|   |  |NXT|PDN|RET|  |   | 4 | 5 | 6 | - |
 * +--------------------------------------------------------|ENT|  +-----------+  | C |---------------+
 * |CTL|SLK| A | S | D | F | G | H | J | K | L |ö é|ä à|$¤£ |   |  |UP |LFT|RGT|  |   | 1 | 2 | 3 |   |
 * +------------------------------------------------------------+  +-----------+  +---------------| + |
 * |SHIFT|#@!| Y | X | C | V | B | N | M | , | . | - | SHIFT|ESC|  |DWN|DEL|INS|  |   0   |000| . |   |
 * +-----+---+---+-------------------------------+---+------+---+  +---+---+---+  +-------+---+---+---+
 *               |            SPACE              |
 *               +-------------------------------+
 *
 */
     
  [0] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_RGUI, KC_HELP, KC_END, KC_SYSREQ, KC_CLEAR, KC_APP, KC_SCROLLLOCK, KC_NUMLOCK, \
    KC_NONUS_BSLASH, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_EXEC, KC_PRIOR, KC_PGUP, KC_HOME, KC_KP_SLASH, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ASTERISK, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_NO, KC_GRAVE, KC_ENTER, KC_NO, KC_PGDOWN, KC_RETURN, KC_CRSEL, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS, \
    KC_LCTRL, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NO, KC_UP, KC_LEFT, KC_RIGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_PLUS, \
    KC_LSHIFT, KC_NONUS_HASH, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSHIFT, KC_ESC, KC_DOWN, KC_DEL, KC_INS, KC_KP_0, KC_KP_COMMA, KC_KP_DOT, \
    KC_SPACE \
  )
} ;
