
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

void led_set(uint8_t usb_led) {
    static uint8_t last_led = 0;

    uint8_t led = 0;
  
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        led |= 1;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        led |= 8;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        led |= 4;
    if (usb_led & (1<<USB_LED_COMPOSE))
        led |= 2;
    if (usb_led & (1<<USB_LED_KANA))
        led |= 0x10;
  
    uint8_t led_on = led & ~last_led;
    if ((led_on & 0x0F) != 0) {
        uint8_t cmd = 0x80 | (led_on & 0x0F);
#if defined(__AVR__)
        serial_send(0x13);
        serial_send(cmd);
#elif defined PROTOCOL_CHIBIOS
        uint8_t leds[2];
        leds[0] = 0x13;
        leds[1] = cmd;
        sdWrite(&SD1, leds, 2);
#endif
    }
#ifdef MS_7004
    if ((led_on & 0x10) != 0) {
#if defined(__AVR__)
        serial_send(0x13);
        serial_send(0x90);
#elif defined PROTOCOL_CHIBIOS
        uint8_t leds[2] = { 0x13, 0x90 };
        sdWrite(&SD1, leds, 2);
#endif
    }
#endif

    uint8_t led_off = ~led & last_led;
    if ((led_off & 0x0F) != 0) {
        uint8_t cmd = 0x80 | (led_off & 0x0F);
#if defined(__AVR__)
        serial_send(0x11);
        serial_send(cmd);
#elif defined PROTOCOL_CHIBIOS
        uint8_t leds[2];
        leds[0] = 0x11;
        leds[1] = cmd;
        sdWrite(&SD1, leds, 2);
#endif
    }
#ifdef MS_7004
    if ((led_off & 0x10) != 0) {
#if defined(__AVR__)
        serial_send(0x11);
        serial_send(0x90);
#elif defined PROTOCOL_CHIBIOS
        uint8_t leds[2] = { 0x11, 0x90 };
        sdWrite(&SD1, leds, 2);
#endif
    }
#endif

    last_led = led;
}
