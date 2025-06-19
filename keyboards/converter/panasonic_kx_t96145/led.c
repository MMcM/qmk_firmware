
#include "led.h"
#include "quantum.h"

#define LED_PIN C7

void led_init_ports(void) {
    gpio_set_pin_output(LED_PIN);
    gpio_write_pin_high(LED_PIN);
}

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        gpio_write_pin_low(LED_PIN);
    } else {
        gpio_write_pin_high(LED_PIN);
    }
}
