
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ 3 │
     * ├───┤
     * │ 2 │
     * ├───┤
     * │ 1 │
     * └───┘
     */
    [0] = LAYOUT_mini(
        KC_3,
        KC_2,
        KC_1
    )
};
