
#include "stdint.h"
#include "led.h"

#define VT100_LED_L4 (1<<0)
#define VT100_LED_L3 (1<<1)
#define VT100_LED_L2 (1<<2)
#define VT100_LED_L1 (1<<3)
#define VT100_LED_KBD_LOCKED (1<<4)
// These two are complements of one another; bit on means LOCAL.
#define VT100_LED_LOCAL (1<<5)
#define VT100_LED_ONLINE (1<<5)

// Until we actually receive a setting from the host.
uint8_t vt100_leds = VT100_LED_LOCAL;

void led_set(uint8_t usb_led) {
    uint8_t leds = 0;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        leds |= VT100_LED_KBD_LOCKED;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        leds |= VT100_LED_L1;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        leds |= VT100_LED_L2;
    if (usb_led & (1<<USB_LED_COMPOSE))
        leds |= VT100_LED_L3;
    if (usb_led & (1<<USB_LED_KANA))
        leds |= VT100_LED_L4;
    vt100_leds = leds;
}
