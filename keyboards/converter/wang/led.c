
#include "debug.h"
#include "host.h"
#include "led.h"
#include "stdint.h"

extern void wang_cmd(uint8_t cmd);

void led_update_ports(led_t led_state) {
    wang_cmd(0x1D);             // All off
    if (led_state.caps_lock) {
        wang_cmd(0x10);         // LED0 on
    }
    if (led_state.num_lock) {
        wang_cmd(0x1A);         // LED5 on
    }
    if (led_state.scroll_lock) {
        wang_cmd(0x18);         // LED4 on
    }
    if (led_state.compose) {
        wang_cmd(0x16);         // LED3 on
    }
    if (led_state.kana) {
        wang_cmd(0x14);         // LED2 on
    }
}
