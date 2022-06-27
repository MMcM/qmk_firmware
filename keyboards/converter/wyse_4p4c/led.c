
#include "stdint.h"
#include "led.h"

extern uint8_t led_count;

void led_set(uint8_t usb_led) {
    uint8_t led = 0;
  
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        led |= 1;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        led |= 2;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        led |= 4;
  
    led_count = led ^ 7;
}
