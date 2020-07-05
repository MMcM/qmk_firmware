
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |Esc|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|Num|Scr|Prt|Sys|Pau|
 * +---------------------------------------------------------------+
 * |<>\|1 !|2"@|3 §|4 $|5 %|6 &|7 /|8 (|9 )|0 =|ß ?|' `|# ^|<- |Hom|
 * +---------------------------------------------------------------+
 * |Tab | Q | W | E | R | T | Z | U | I | O | P |Ü [|+*]|      |PUp|
 * +----------------------------------------------------|      |---+
 * |Ctrl | A | S | D | F | G | H | J | K | L | Ö | Ä | Enter   |PDn|
 * +---------------------------------------------------------------+
 * | Shift | Y | X | C | V | B | N | M |, ;|. :|-_+| Shift |Up |End|
 * +---------------------------------------------------------------+
 * |Alt |Caps|Trb|                             |Ins|Del|Lft|Dwn|Rgt|
 * +---------------------------------------------------------------+
 *
 */
     
  [0] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NUMLOCK, KC_SCROLLLOCK, KC_PSCREEN, KC_SYSREQ, KC_PAUSE, \
    KC_BSLASH, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_SLASH, KC_GRAVE, KC_NONUS_HASH, KC_BSPACE, KC_HOME, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_PGUP, \
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_PGDN, \
    KC_LSHIFT, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_MINUS, KC_RSHIFT, KC_UP, KC_END, \
    KC_LALT, KC_CAPSLOCK, KC_NO, KC_SPACE, KC_INS, KC_DEL, KC_LEFT, KC_DOWN, KC_RIGHT \
  )
} ;
