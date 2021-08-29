
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   +---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+----+ +---+ +---+---+---+   +---+---+---+ +---+
 *   |COD| |   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS | |COD| |STP|CHR|IN |   |   |   |   | | - |
 *   +---+ +   |----------------------------------------------------+ +---+ +-----------+   +-----------+ +---+
 *   |CTS| | TAB | Q | W | E | R | T | Y | U | I | O | P | ! |RETURN| |INS| |SKP|WRD|OUT|   | 7 | 8 | 9 | | , |
 *   +---+ +--------------------------------------------------|     | +---+ +-----------+   +-----------+ +---+
 *   |HLD| | LOCK | A | S | D | F | G | H | J | K | L | ; | ' |     | |PRG| |ADJ|LIN|PRT|   | 4 | 5 | 6 | | . |
 *   +---+ +--------------------------------------------------------+ +---+ +-----------+   +-----------+ +---+
 *   |SET| | SHIFT  | Z | X | C | V | B | N | M | , | . | / | SHIFT | |MOV| |UP |PAR|   |   | 1 | 2 | 3 | |ENT|
 *   +---+ +--------+---------------------------------------+-------+ +---+ +-----------+   +-----------+ |   |
 *   |REL|            |                                   |           |ERS| |DWN|PAG|   |   |     0     | |   |
 *   +---+            +-----------------------------------+           +---+ +---+---+---+   +-----------+ +---+
 *
 */
     
  [0] = LAYOUT(
    KC_ESC,       KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE,  KC_BSLASH,    KC_PAUSE, KC_F13, KC_INSERT,       KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK,  KC_KP_MINUS, \
    KC_GRAVE,     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_ENTER,  KC_RBRACKET,  KC_SCROLLLOCK, KC_F14, KC_DELETE,  KC_KP_7, KC_KP_8, KC_KP_9,                KC_KP_PLUS, \
    KC_CAPSLOCK,  KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE,        KC_RCTRL,     KC_HOME, KC_END, KC_PSCREEN,       KC_KP_4, KC_KP_5, KC_KP_6,                KC_KP_DOT, \
    KC_LGUI,      KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_RGUI,      KC_UP, KC_PGUP, KC_LEFT,           KC_KP_1, KC_KP_2, KC_KP_3,                KC_KP_ENTER, \
    KC_LALT,      KC_SPACE,                                                                                   KC_RALT,      KC_DOWN, KC_PGDOWN, KC_RIGHT,      KC_KP_0
  )
} ;
