
#pragma once

/*
 * The keybaord PCB hardware drives the thirteen LEDs with two NE5090 addressable relay drivers.
 * The protocol supports up to 32 LEDs, so the controller firmware needs to map logical LED number
 * (inside the box) to a driver selector and position (10 bit and 07 bits, respectively, shown 
 * outside the box).
 *
 *  13  12  11  10           7   6   5   4
 * .................       +---+---+---+---+     +---------------+    +---------------+
 * |05 |01 |09 |0D |       |0C |10 |14 |18 |     |               |    |               |
 * .................       +---+---+---+---+     +---------------+    +---------------+

 * +---------------------------------------------------------------+  +---------------+     +---+
 * |                                                               |  |               |     |08 |3
 * |                                                               |  |               |     +---+
 * |                                                               |  |               |     |00 |2
 * |                                                               |  |               |     +---+
 *  |                                                             |   |               |     |03 |1
 *  |-+---+                                                       |   +               |     +---+
 *    |04 |14                                                     |   |               |     |02 |0
 *    +---+----------                               --------------+   +---------------+     +---+
 *                  |                               |
 *                  +-------------------------------+
 *
 * Protocol:
 *     0x12 - turn off all LEDs
 *     0x13 - turn on all LEDs
 *     0x20 | LED number (above) - turn on single LED
 *     0x40 | LED number (above) - turn off single LED
 *
 * The fourteenth LED (16) is actually a 555 timer to connected to the internal speaker.
 * Its protocol address is 1F. Turning it on, that is, sending 0x3F, beeps.
 */

#define TEK_LED_VIEW 0x02
#define TEK_LED_NEXT_VIEW 0x03
#define TEK_LED_PAN 0x00
#define TEK_LED_ZOOM 0x08
#define TEK_LED_HARD_COPY 0x18
#define TEK_LED_LOCAL 0x14
#define TEK_LED_SET_UP 0x10
#define TEK_LED_DIALOG 0x0C
#define TEK_LED_RCV 0x0D
#define TEK_LED_XMT 0x09
#define TEK_LED_PAGE_FULL 0x01
#define TEK_LED_KYBD_LOCK 0x05
#define TEK_LED_CAPS_LOCK 0x04
#define TEK_LED_BEEP 0x1F
#define TEK_LED_NONE 0xFF

#define TEK_LED_CMD_ALL_OFF 0x12
#define TEK_LED_CMD_ALL_ON 0x13
#define TEK_LED_CMD_OFF 0x40
#define TEK_LED_CMD_ON 0x20

void led_reset(void);
void led_init(void);
uint32_t led_get_extra(void);
void led_set_extra(uint32_t extra);
uint8_t led_for_key(uint8_t key);
