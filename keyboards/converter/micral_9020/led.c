
#include "debug.h"
#include "host.h"
#include "led.h"
#include "stdint.h"

#include "uart.h"

void led_update_ports(led_t led_state) {
    uint8_t leds = 0xDF;
    if (led_state.num_lock) {
        leds &= ~0x01;
    }
    if (led_state.scroll_lock) {
        leds &= ~0x02;
    }
    if (led_state.compose) {
        leds &= ~0x04;
    }
    if (led_state.kana) {
        leds &= ~0x08;
    }
    dprintf("X: %02X\n", leds);
    uart_write(leds);
}
