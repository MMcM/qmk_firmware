
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#ifndef SD_KEYBOARD
#define SD_KEYBOARD SD3
#endif
#endif

void led_set(uint8_t usb_led) {
    uint8_t led = 0;
  
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        led |= 1;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        led |= 2;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        led |= 4;
    if (usb_led & (1<<USB_LED_COMPOSE))
        led |= 8;
    if (usb_led & (1<<USB_LED_KANA))
        led |= 16;

    uint8_t led1 = (led << 5) & 0x60;
#if defined(__AVR__)
    serial_send(led1);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD_KEYBOARD, &led1, 1);
#endif

    uint8_t led2 = (led & ~3) | 1;
#if defined(__AVR__)
    serial_send(led2);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD_KEYBOARD, &led2, 1);
#endif
}
