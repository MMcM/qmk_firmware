/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_END, KC_HOME, KC_MUTE,
        MO(1),  KC_MPLY, KC_MSTP,
        KC_F1,  KC_F2,   KC_F3
    ),
    [1] = LAYOUT(
        QK_BOOT, RGB_TOG, RGB_MOD,
        _______, _______, _______,
        DEBUG,   _______, _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        switch (biton32(layer_state)) {
        case 1:
            if (clockwise) {
                rgb_matrix_increase_hue();
            } else {
                rgb_matrix_decrease_hue();
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
            break;
        }
    }
    else if (index == _MIDDLE) {
        switch (biton32(layer_state)) {
        case 1:
            if (clockwise) {
                rgb_matrix_increase_sat();
            } else {
                rgb_matrix_decrease_sat();
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        }
    }
    else if (index == _RIGHT) {
        switch (biton32(layer_state)) {
        case 1:
            if (clockwise) {
                rgb_matrix_increase_val();
            } else {
                rgb_matrix_decrease_val();
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        }
    }
    return true;
}
