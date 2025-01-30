
#include "stdint.h"
#include "led.h"

extern uint8_t led_count;

void led_update_ports(led_t led_state) {
    uint8_t led = 0;
  
    if (led_state.scroll_lock)
        led |= 1;
    if (led_state.num_lock)
        led |= 2;
    if (led_state.caps_lock)
        led |= 4;
  
    led_count = led ^ 7;
}
