/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#if defined(__AVR__)
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

#if defined(__AVR__)
#define sun_send serial_send
#elif defined PROTOCOL_CHIBIOS
static inline void sun_send(uint8_t data) {
    sdWrite(&SD1, &data, 1);
}
#endif

void led_set(uint8_t usb_led)
{
    uint8_t sun_led = 0;
    if (usb_led & (1<<USB_LED_NUM_LOCK))    sun_led |= (1<<0);
    if (usb_led & (1<<USB_LED_COMPOSE))     sun_led |= (1<<1);
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) sun_led |= (1<<2);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))   sun_led |= (1<<3);
    xprintf("LED: %02X\n", usb_led);

    sun_send(0x0E);
    sun_send(sun_led);
}
