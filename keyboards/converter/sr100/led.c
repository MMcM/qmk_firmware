
#include "led.h"

bool led_is_pending;
uint8_t pending_leds;

void led_update_ports(led_t led_state) {
    // Set the covered LED and thereby clear SEND (POLL).
    // Skip RCV (SEL).
    uint8_t leds = 1;
    // LOCAL
    if (led_state.num_lock) {
        leds |= 1 << 2;
    }
    // FORMS
    if (led_state.scroll_lock) {
        leds |= 1 << 3;
    }
    // BACKGRND POLL/SEL
    if (led_state.compose) {
        leds |= 1 << 4;
    }
    // LTAI
    if (led_state.kana) {
        leds |= 1 << 5;
    }
    // Inside CAPS LOCK switch
    if (led_state.caps_lock) {
        leds |= 1 << 6;
    }
    // The 8th bit is the piezo speaker.
    pending_leds = leds;
    led_is_pending = true;
}
