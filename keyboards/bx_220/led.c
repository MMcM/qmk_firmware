
#include "stdint.h"
#include "led.h"
#include "quantum.h"

#define LED_MASK_HOLD_SCREEN (1<<0)
#define LED_MASK_LOCK (1 << 1)
#define LED_MASK_COMPOSE (1 << 2)
#define LED_MASK_WAIT (1 << 3)

static uint8_t led_pins[NLEDS] = LED_PINS;

void led_init_ports(void) {
    gpio_set_pin_output(LED_STROBE_PIN);
}

void led_update_ports(led_t led_state) {
    uint8_t mask = 0;
    if (led_state.scroll_lock)
        mask |= LED_MASK_HOLD_SCREEN;
    if (led_state.num_lock)
        mask |= LED_MASK_WAIT;
    if (led_state.caps_lock)
        mask |= LED_MASK_LOCK;
    if (led_state.compose)
        mask |= LED_MASK_COMPOSE;

    for (uint8_t led = 0; led < NLEDS; led++) {
        gpio_set_pin_output(led_pins[led]);
        if ((mask & (1 << led)) != 0) {
            gpio_write_pin_low(led_pins[led]);
        } else {
            gpio_write_pin_high(led_pins[led]);
        }
    }
    gpio_write_pin_high(LED_STROBE_PIN);
    wait_us(10);
    gpio_write_pin_low(LED_STROBE_PIN);
    for (uint8_t led = 0; led < NLEDS; led++) {
        gpio_set_pin_input_high(led_pins[led]);
    }
}
