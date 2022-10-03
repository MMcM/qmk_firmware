
#include "stdint.h"
#include "led.h"

#define COLOR_10_LED_L4 (1<<0)
#define COLOR_10_LED_L3 (1<<1)
#define COLOR_10_LED_L2 (1<<2)
#define COLOR_10_LED_L1 (1<<3)
#define COLOR_10_LED_KBD_LOCKED (1<<4)
// These two are complements of one another; bit on means ONLINE.
#define COLOR_10_LED_LOCAL (1<<5)
#define COLOR_10_LED_ONLINE (1<<5)

#define COLOR_10_BEEP (1 << 8)

// Until we actually receive a setting from the host, show LOCAL.
uint8_t color_10_leds = 0;

void led_set(uint8_t usb_led) {
    uint8_t leds = COLOR_10_LED_ONLINE;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        leds |= COLOR_10_LED_KBD_LOCKED;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        leds |= COLOR_10_LED_L1;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        leds |= COLOR_10_LED_L2;
    if (usb_led & (1<<USB_LED_COMPOSE))
        leds |= COLOR_10_LED_L3;
    if (usb_led & (1<<USB_LED_KANA))
        leds |= COLOR_10_LED_L4;
    color_10_leds = leds;
}
