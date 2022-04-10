
#include "stdint.h"
#include "led.h"
#include "m24.h"

void led_set(uint8_t usb_led) {
    static uint8_t current = 0;
    uint8_t leds = 0;

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        leds |= 1;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        leds |= 2;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        leds |= 4;

    if (current != leds) {
        uint8_t on = leds & ~current;
        if (on != 0) {
            m24_send(0x13);
            m24_send(0x80 | on);
        }
        uint8_t off = current & ~leds;
        if (off != 0) {
            m24_send(0x13);
            m24_send(off);
        }
        current = leds;
    }
}
