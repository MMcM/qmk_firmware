
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | BS  | |Clr| - | + | * |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] | \ | | 7 | 8 | 9 | / |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Caps | A | S | D | F | G | H | J | K | L | ; | ' |Return| | 4 | 5 | 6 | , |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | Shift  | Z | X | C | V | B | N | M | , | . | / |  Shift | | 1 | 2 | 3 |   |
 * +---------------------------------------------------------+ +-------+---|Ent|
 *     |Opt|Apple|                                 |Enter|Opt| |   0   | . |   |
 *     +-----------------------------------------------------+ +-------+---+---+
 *
 * The two Shift keys do not have separate scan codes.
 */
     
    [0] = LAYOUT(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL,     KC_BSPACE,     KC_DELETE, KC_KP_MINUS, KC_KP_PLUS, KC_KP_ASTERISK, \
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSLASH,     KC_KP_7,   KC_KP_8,     KC_KP_9,    KC_KP_SLASH, \
        KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE,       KC_ENTER,      KC_KP_4,   KC_KP_5,     KC_KP_6,    KC_KP_COMMA, \
        KC_LSHIFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH,         KC_RSHIFT,     KC_KP_1,   KC_KP_2,     KC_KP_3,    KC_KP_ENTER, \
        KC_LALT, KC_LGUI, KC_SPACE,                                                     KC_APPLICATION, KC_RALT,     KC_KP_0,   KC_KP_DOT \
    )
} ;
