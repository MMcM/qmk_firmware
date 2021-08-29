
#include QMK_KEYBOARD_H

enum user_keycodes {
    RBRC_OR_PDOT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Combined
 *
 * +---++---++---+---+---+---+---++---+---+---+---+---++---+---+ +---+---+---+ +---+---+---+---+
 * |BRK||CPY||PF1|PF2|PF3|PF4|PF5||PF6|PF7|PF8|PF9|F10||F11|F12| |辞書|抹消|登録| |F13|F14|F15|F16|
 * +---++---++---+---+---+---+---++---+---+---+---+---++---+---+ +-----------+ ----------------+
 *                                                               |前行|HOM|次行| |F17|F18|F19|F20|
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +-----------+ +---+---+---+---+
 * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ | ¥ | ] | |半角|削除|挿入|
 * +-----------------------------------------------------------+ +---+---+---+ +---+---+---+---+
 * |英字  | Q | W | E | R | T | Y | U | I | O | P | : | [ |  ⏎  |               | * | / | + | - |
 *                                               | @ |                                          
 * +------------------------------------------------------|    |     +---+     +---------------+
 * |英小文字| A | S | D | F | G | H | J | K | L | ; |後退|取消|   | +---| ↑ |---+ | 7 | 8 | 9 | = |
 * +-----------------------------------------------------------+ | ← |---| → | +---------------+
 * | SHIFT  | Z | X | C | V | B | N | M | , | . | / | " | SHIFT| +---| ↓ |---+ | 4 | 5 | 6 | . |
 * +-----------------------------------------------------------+     +---+     +---------------|
 * | CTRL| ALT | タブ | 親指左  | 親指右 |        空白         |かな|               | 1 | 2 | 3 | ⏎ |
 * | ひらがな |  CAP   |                          |  カタカナ  |                                     
 * +-----+-----+-----+---+---------+---+-------------------+---+ +-----------+ +-----------|   |
 *                       |無変換|変換|                             |    実行    | |   0   |000|   |
 *                       +----+----+                             +-----------+ +-------+---+---+
 */

  [0] = LAYOUT(
    KC_PAUS, KC_PSCR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_NO,    KC_NO,   KC_NO,    KC_F13,  KC_F14,  KC_F15,  KC_F16, \
                                                                                                              KC_PGUP,  KC_HOME, KC_PGDN,  KC_F17,  KC_F18,  KC_F19,  KC_F20, \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, RBRC_OR_PDOT,    KC_LANG5, KC_DEL,  KC_INS, \
    KC_INT2, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_RO, KC_GRV, KC_LBRC, KC_ENT,                                    KC_PAST, KC_PSLS, KC_PPLS, KC_PMNS, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_BSPC, KC_ESC,                            KC_UP,             KC_P7,   KC_P8,   KC_P9,   KC_PEQL, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT, KC_RSFT,            KC_LEFT,  KC_DOWN, KC_RGHT,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, \
    KC_LCTRL, KC_LALT, KC_TAB, KC_LANG1, KC_LANG2, KC_SPACE, KC_KANA, KC_LANG4, KC_CAPS, KC_KANA,                                                KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
                   KC_MHEN, KC_HENK,                                                                          KC_RGUI,                     KC_P0,            KC_PCMM
  )
} ;

extern bool oasys_is_jis;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RBRC_OR_PDOT:
        keycode = oasys_is_jis ? KC_RBRC : KC_PDOT;
        break;
    // TODO: More like that?
    default:
        return true;
    }
    if (record->event.pressed) {
        register_code(keycode);
    } else {
        unregister_code(keycode);
    }
    return false;
}
