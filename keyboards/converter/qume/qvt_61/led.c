
#include "stdint.h"
#include "led.h"

#define LED_MASK_HOLD_SCREEN (1<<0)
#define LED_MASK_COMPOSE (1 << 1)
#define LED_MASK_WAIT (1 << 2)
#define LED_MASK_LOCK (1 << 3)

extern uint8_t led_mask;
extern bool led_pending;

void led_set(uint8_t usb_led) {
    uint8_t mask = 0;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        mask |= LED_MASK_HOLD_SCREEN;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        mask |= LED_MASK_WAIT;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        mask |= LED_MASK_LOCK;
    if (usb_led & (1<<USB_LED_COMPOSE))
        mask |= LED_MASK_COMPOSE;
    if (led_mask != mask) {
        led_mask = mask;
        led_pending = true;
    }
}
