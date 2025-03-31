
#include "debug.h"
#include "matrix.h"
#include "quantum.h"

#define DATA_PORT PORTB
#define DATA_PIN PINB
#define DATA_DDR DDRB
#define ROW_MASK 0x0F

#define LED_PIN D0
#define ROW_PIN D1
#define RESET_PIN D2

void matrix_init_custom(void) {
    DATA_DDR = 0x00;
    DATA_PORT = 0xFF;
    gpio_set_pin_output(LED_PIN);
    gpio_write_pin_high(LED_PIN);
    gpio_set_pin_output(ROW_PIN);
    gpio_write_pin_high(ROW_PIN);
    gpio_set_pin_output(RESET_PIN);
    gpio_write_pin_high(RESET_PIN);
}

bool led_is_pending = true;
uint8_t pending_leds = 0x00;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (led_is_pending) {
        DATA_DDR = 0xFF;
        DATA_PORT = pending_leds;
        gpio_write_pin_low(LED_PIN);
        wait_us(1);
        gpio_write_pin_high(LED_PIN);
        DATA_DDR = 0x00;
        led_is_pending = false;
    }

    bool changed = false;

    // Load row address into driver.
    static uint8_t row = 0;
    DATA_DDR = ROW_MASK;
    DATA_PORT = (DATA_PORT & ~ROW_MASK) | (row & ROW_MASK);
    gpio_write_pin_low(ROW_PIN);
    wait_us(1);
    gpio_write_pin_high(ROW_PIN);
    DATA_DDR = 0x00;

    // Read key states.
    wait_us(10);
    uint8_t cols = ~DATA_PIN;

    // Reset sense amp.
    gpio_write_pin_low(RESET_PIN);
    wait_us(1);
    gpio_write_pin_high(RESET_PIN);

    if (current_matrix[row] != cols) {
        current_matrix[row] = cols;
        changed = true;
    }

    row = (row + 1) & ROW_MASK;

    return changed;
}
