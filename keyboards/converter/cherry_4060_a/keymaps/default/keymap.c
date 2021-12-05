
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *
 *     +---+---+---+---+
 *     |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 * |   |   |   |   |   |   |
 * +---+---------------+---+
 *     |   |   |   |   |
 *     +---+---+---+---+
 *
 */

  [0] = LAYOUT(
    KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, BL_TOGG, \
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, \
    KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
    KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, \
    KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, \
    KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_STOP, KC_MEDIA_NEXT_TRACK \
  )
} ;

#ifdef LED_MATRIX_ENABLE

#include "led_matrix.h"

#ifndef LED_MATRIX_KEYPRESSES
// Light the last key hit (without fade).
static uint8_t last_led_index = 0xFF;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
#ifdef LED_MATRIX_KEYPRESSES
    // Update g_last_hit_tracker.
    process_led_matrix(record->event.key.row, record->event.key.col, record->event.pressed);
#else
    // Cheaper version for just tracking one.
    if (record->event.pressed) {
        uint8_t led[1];
        if (led_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led) > 0) {
            last_led_index = led[0];
        }
    }
#endif
    return true;
}

void led_matrix_indicators_kb(void) {
#ifdef LED_MATRIX_KEYPRESSES
    // Heatmap but with fewer possible PWM values.
    led_matrix_set_value_all(0);
    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = 0; i < count; i++) {
        uint16_t tick = g_last_hit_tracker.tick[i];
        if (tick < 255) {
            uint8_t value;
            if (tick < 64) {
                value = LED_MATRIX_MAXIMUM_BRIGHTNESS;
            } else if (tick < 128) {
                value = LED_MATRIX_MAXIMUM_BRIGHTNESS / 2;
            } else {
                value = LED_MATRIX_MAXIMUM_BRIGHTNESS / 4;
            }
            led_matrix_set_value(g_last_hit_tracker.index[i], value);
        }
    }
#else
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led_matrix_set_value(i, i == last_led_index ? LED_MATRIX_MAXIMUM_BRIGHTNESS : 0);
    }
#endif
}

#endif
