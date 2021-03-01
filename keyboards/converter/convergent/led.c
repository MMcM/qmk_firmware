
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

// The LEDs are f10, f9, f8, f3, f2, f1, LOCK, OVERTYPE

void led_set(uint8_t usb_led) {
    uint8_t leds[2] = { 0xA0, 0xB0 };
  
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        leds[0] |= 2;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        leds[0] |= 1;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        leds[1] |= 4;
    if (usb_led & (1<<USB_LED_COMPOSE))
        leds[1] |= 8;
    if (usb_led & (1<<USB_LED_KANA))
        leds[1] |= 2;
  
#if defined(__AVR__)
    serial_send(leds[0]);
    serial_send(leds[1]);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, leds, 2);
#endif
}
