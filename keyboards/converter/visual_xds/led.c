
#include "stdint.h"
#include "led.h"
#include <avr/io.h>
#include "protocol/serial.h"

void led_set(uint8_t usb_led) {
    uint8_t led = 0;

    // Some of the higher bits control the beeper.

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        led |= 1;               // Error
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        led |= 2;               // Lock
    if (usb_led & (1<<USB_LED_COMPOSE))
        led |= 4;               // Compose
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        led |= 0x10;            // Wait

    serial_send(led);
}
