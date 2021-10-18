
#include "stdint.h"
#include "led.h"
#include "quantum.h"

#define LED_MASK_HOLD_SCREEN (1<<0)
#define LED_MASK_LOCK (1 << 1)
#define LED_MASK_COMPOSE (1 << 2)
#define LED_MASK_WAIT (1 << 3)

static uint8_t led_pins[NLEDS] = LED_PINS;

void led_init_ports(void) {
    setPinOutput(LED_STROBE_PIN);
}

void led_set(uint8_t usb_led) {
    uint8_t mask = 0;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        mask |= LED_MASK_HOLD_SCREEN;
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        mask |= LED_MASK_WAIT;
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        mask |= LED_MASK_LOCK;
    if (usb_led & (1<<USB_LED_COMPOSE))
        mask |= LED_MASK_COMPOSE;

    for (uint8_t led = 0; led < NLEDS; led++) {
        setPinOutput(led_pins[led]);
        if ((mask & (1 << led)) != 0) {
            writePinLow(led_pins[led]);
        } else {
            writePinHigh(led_pins[led]);
        }
    }
    writePinHigh(LED_STROBE_PIN);
    wait_us(10);
    writePinLow(LED_STROBE_PIN);
    for (uint8_t led = 0; led < 4; led++) {
        setPinInputHigh(led_pins[led]);
    }
}
