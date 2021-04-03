
#include "stdint.h"
#include "led.h"

#define LED_ALPHA_LOCK 0x02
#define LED_ON_LINE 0x04
#define BUZZER_OFF 0x08
#define LED_F19 0x10
#define LED_F20 0x80

extern uint8_t led_buzzer_state;

void led_set(uint8_t usb_led) {
    uint8_t new_state = BUZZER_OFF;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        new_state |= LED_ALPHA_LOCK;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        new_state |= LED_ON_LINE;
    if (usb_led & (1<<USB_LED_COMPOSE))
        new_state |= LED_F19;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        new_state |= LED_F20;
    led_buzzer_state = new_state;
}
