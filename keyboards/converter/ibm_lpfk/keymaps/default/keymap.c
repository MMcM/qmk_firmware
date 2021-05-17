
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
extern uint8_t g_last_led_hit[];
extern uint8_t g_last_led_count;

// Track g_last_led_xxx on key press.
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    process_led_matrix(keycode, record);
    return true;
}

// Light the last key hit (no fade possible with only on/off).
void led_matrix_indicators_kb(void) {
    static uint8_t last_led_index = 0xFF;
    if (g_last_led_count > 0) {
        last_led_index = g_last_led_hit[0];
    }
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led_matrix_set_index_value(i, i == last_led_index ? LED_MATRIX_MAXIMUM_BRIGHTNESS : 0);
    }
}

#endif
