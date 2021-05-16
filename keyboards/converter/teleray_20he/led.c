
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

void led_set(uint8_t usb_led) {
    uint8_t mask = 0;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        mask |= 2;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        mask |= 4;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        mask |= 8;
    if (usb_led & (1<<USB_LED_COMPOSE))
        mask |= 0x10;
  
#if defined(__AVR__)
    serial_send(mask);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, &mask, 1);
#endif
}
