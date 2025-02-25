
#include "led.h"

#define LED_MASK_HOLD_SCREEN (1<<0)
#define LED_MASK_COMPOSE (1 << 1)
#define LED_MASK_WAIT (1 << 2)
#define LED_MASK_LOCK (1 << 3)

extern uint8_t led_mask;
extern bool led_pending;

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
    if (led_mask != mask) {
        led_mask = mask;
        led_pending = true;
    }
}
