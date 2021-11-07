
#include QMK_KEYBOARD_H

enum macros {
    M_0 = SAFE_RANGE,
    M_S1, M_S2, M_S3, M_S4, M_S5, M_S6, M_S7, M_S8,
    M_C1, M_C2, M_C3, M_C4, M_C5, M_C6, M_C7, M_C8,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * .---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
 * |Cmd|Lrn|  |BTy|   |S1 |S2 |S3 |S4 |  |S5 |S6 |S7 |S8 |   |Fnt|Lok|  |PgA|PgB|  |Mov|Scl|  +---+---+     +---+   +-----+
 * .-------.  .---.   .---------------.  .---------------.   .-------.  .-------.  .-------.  |CPv|CPg|     |Swp|   |SavFl|
 * |Hlp|   |  |BGr|   |C1 |C2 |C3 |C4 |  |C5 |C6 |C7 |C8 |   |Sdr|Eff|  |   |   |  |Row|Krn|  +---+---+     +---+   +-----+
 * .---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
 * +---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
 * |Und|Red|  |Esc|   |F1 |F2 |F3 |F4 |  |F5 |F6 |F7 |F8 |  |F9 |F10|F11|F12|  |Prt|Scl|Pau|
 * +---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
 * +---+---+  +---+---+---+---+---+---+---+---+---+---+---+---+---+---------+  +---+---+---+  .---.---.  +---+---+---+---+
 * |Sty|Tab|  | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backspace|  |Ins|Hom|PUp|  |Seq|Mac|  |Num| / | * | - |
 * +-------+  +-------------------------------------------------------------+  +-----------+  .-------.  +---------------+
 * |Ctr|Low|  | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |   \   |  |Del|End|PDn|  |Stp|Ply|  | 7 | 8 | 9 |   |
 * +-------+  +-------------------------------------------------------------+  +---+---+---+  .---.---.  +------------ + +
 * |   |Jst|  | Caps | A | S | D | F | G | H | J | K | L | ; | ' | Enter    |      | U |      .---.---.  | 4 | 5 | 6 |   |
 * +-------+  +-------------------------------------------------------------+  +---+---+---+  |Prv|Pgm|  +---------------+
 * |   |   |  | Shift  | Z | X | C | V | B | N | M | , | . | / |  Shift     |  | L | D | R |  .---.---.  | 1 | 2 | 3 |   |
 * +-------+  +-------------------------------------------------------------+  +-----------+  +-------+  +------------ E +
 * |Dek|Mac|  |Ctrl |    | Alt |                           | Alt |    |Ctrl |  |Chr|Row|Lay|  |RPv|RPg|  |   0   | . |   |
 * +-------+  +-----+    +---------------------------------------+    +-----+  +---+---+---+  +-------+  +---------------+
 */

  [0] = LAYOUT(
    KC_NO, KC_NO,     KC_NO,   M_S1, M_S2, M_S3, M_S4, M_S5, M_S6, M_S7, M_S8,        KC_NO, KC_NO,          KC_NO, KC_NO,     KC_NO, KC_NO,       KC_NO, KC_NO,   KC_NO, KC_NO, \
    KC_HELP, KC_NO,   KC_NO,   M_C1, M_C2, M_C3, M_C4, M_C5, M_C6, M_C7, M_C8,        KC_NO, KC_NO,          KC_NO, KC_NO,     KC_NO, KC_NO, \
    KC_UNDO, KC_AGIN, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_PSCR, KC_SLCK,  KC_PAUS, \
    KC_NO, KC_NO,     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,   KC_INS,  KC_HOME,  KC_PGUP,  KC_NO, KC_NO,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
    KC_NO, KC_NO,     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL,  KC_END,   KC_PGDN,  KC_NO, KC_NO,   KC_P7, KC_P8, KC_P9, KC_PPLS, \
    KC_NO, KC_NO,     KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                 KC_UP,              KC_NO, KC_NO,   KC_P4, KC_P5, KC_P6, \
    KC_NO, KC_NO,     KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,           KC_LEFT, KC_DOWN, KC_RGHT,                   KC_P1, KC_P2, KC_P3, KC_PENT, \
    KC_NO, KC_LGUI,   KC_LCTL, KC_LALT, KC_SPC, KC_RALT, KC_RCTL,                                                     KC_RGUI, KC_MENU, KC_NO,     KC_NO, KC_NO,   KC_P0, KC_PDOT \
  )
};

#ifdef LED_MATRIX_ENABLE

#include "led_matrix.h"

// Blink the last key hit.
static uint8_t last_led_index = 0xFF;

void led_matrix_indicators_kb(void) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led_matrix_set_value(i, i == last_led_index ? 2 : 0);
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case M_S1:
            SEND_STRING("Style 1\n");
            break;
        case M_S2:
            SEND_STRING("Style 2\n");
            break;
        case M_S3:
            SEND_STRING("Style 3\n");
            break;
        case M_S4:
            SEND_STRING("Style 4\n");
            break;
        case M_S5:
            SEND_STRING("Style 5\n");
            break;
        case M_S6:
            SEND_STRING("Style 6\n");
            break;
        case M_S7:
            SEND_STRING("Style 7\n");
            break;
        case M_S8:
            SEND_STRING("Style 8\n");
            break;
        case M_C1:
            SEND_STRING("Color 1\n");
            break;
        case M_C2:
            SEND_STRING("Color 2\n");
            break;
        case M_C3:
            SEND_STRING("Color 3\n");
            break;
        case M_C4:
            SEND_STRING("Color 4\n");
            break;
        case M_C5:
            SEND_STRING("Color 5\n");
            break;
        case M_C6:
            SEND_STRING("Color 6\n");
            break;
        case M_C7:
            SEND_STRING("Color 7\n");
            break;
        case M_C8:
            SEND_STRING("Color 8\n");
            break;
        }
#ifdef LED_MATRIX_ENABLE
        uint8_t led[1];
        if (led_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led) > 0) {
            last_led_index = led[0];
        }
#endif
    }
    return true;
}
