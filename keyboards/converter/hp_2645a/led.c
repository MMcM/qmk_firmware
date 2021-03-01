
#include "stdint.h"
#include "led.h"

/*
 * From left to right, the leds are numbered as follows:
 *   top row: 1, 7, 6 (amber), 5 (green EDIT).
 *   bottom row: 3, 4 (TRANSMIT), 2.
 * Note: 6 and 7 are revered in the diagram in the manual.
 */

#define HP_LED_1 (1<<0)
#define HP_LED_2 (1<<1)
#define HP_LED_3 (1<<2)
#define HP_LED_4 (1<<3)
#define HP_LED_5 (1<<4)
#define HP_LED_6 (1<<5)
#define HP_LED_7 (1<<6)

void led_set(uint8_t usb_led) {
    uint8_t led_mask = 0;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        led_mask |= HP_LED_6;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        led_mask |= HP_LED_3;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        led_mask |= HP_LED_7;
    if (usb_led & (1<<USB_LED_COMPOSE))
        led_mask |= HP_LED_1;
    if (usb_led & (1<<USB_LED_KANA))
        led_mask |= HP_LED_2;
    BUS_DDR = 0xFF;
    BUS_PORT = led_mask;
    LED_OUT_PORT |= LED_OUT_MASK;
    asm("nop\n\t");               // 7475 latch needs 20ns.
    LED_OUT_PORT &= ~LED_OUT_MASK;
    BUS_DDR = BUS_PORT = 0x00;
}
