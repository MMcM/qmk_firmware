
#include "debug.h"
#include "host.h"
#include "led.h"
#include "stdint.h"

#include <avr/io.h>
#include "protocol/serial.h"

#include "tek_led.h"

static uint32_t current_leds;
static uint32_t extra_leds;
static bool led_init_pending;

static inline bool popcount_greater_than_one(uint32_t n) {
    return (n & (n - 1)) != 0;
}

static void led_send_cmd(uint8_t cmd) {
    dprintf("X: %02X\n", cmd);
    serial_send(cmd);
}

void led_reset(void) {
    // Power-on state is all LEDs lit.
    current_leds = 0xFFFFFFFF;
    extra_leds = 0;
    led_init_pending = true;
}

void led_init(void) {
    led_init_pending = false;
    led_set(host_keyboard_leds());
#if 1
    led_send_cmd(TEK_LED_CMD_ON | TEK_LED_BEEP);
#endif
}

uint32_t led_get_extra(void) {
    return extra_leds;
}

void led_set_extra(uint32_t extra) {
    extra_leds = extra;
    led_set(host_keyboard_leds());
}

void led_set(uint8_t usb_led) {
    if (led_init_pending) {
        return;
    }

    uint32_t leds = extra_leds;
    if ((usb_led & (1 << USB_LED_NUM_LOCK)) != 0) {
        leds |= ((uint32_t)1 << TEK_LED_DIALOG);
    }
    if ((usb_led & (1 << USB_LED_CAPS_LOCK)) != 0) {
        leds |= ((uint32_t)1 << TEK_LED_CAPS_LOCK);
    }
    if ((usb_led & (1 << USB_LED_SCROLL_LOCK)) != 0) {
        leds |= ((uint32_t)1 << TEK_LED_LOCAL);
    }
    if ((usb_led & (1 << USB_LED_COMPOSE)) != 0) {
        leds |= ((uint32_t)1 << TEK_LED_SET_UP);
    }
    if ((usb_led & (1 << USB_LED_KANA)) != 0) {
        leds |= ((uint32_t)1 << TEK_LED_PAGE_FULL);
    }
    if (leds == current_leds) {
        return;
    }
    uint32_t changed = leds ^ current_leds;
    if (popcount_greater_than_one(changed)) {
        if (!popcount_greater_than_one(~leds)) {
            led_send_cmd(TEK_LED_CMD_ALL_ON);
            changed = ~leds;          // Ones we need to turn _off_.
        } else {
            led_send_cmd(TEK_LED_CMD_ALL_OFF);
            changed = leds;
        }
    }
    for (uint8_t i = 0; i < 32; i++) {
        if ((changed & (1 << i)) != 0) {
            led_send_cmd((((leds & (1 << i)) == 0) ? TEK_LED_CMD_OFF : TEK_LED_CMD_ON) | i);
        }
    }
    current_leds = leds;
}

uint8_t led_for_key(uint8_t key) {
    switch (key) {
    case 0x2B:
        return TEK_LED_VIEW;
    case 0x2A:
        return TEK_LED_NEXT_VIEW;
    case 0x29:
        return TEK_LED_PAN;
    case 0x28:
        return TEK_LED_ZOOM;
    case 0x2F:
        return TEK_LED_HARD_COPY;
    case 0x2C:
        return TEK_LED_LOCAL;
    case 0x2E:
        return TEK_LED_SET_UP;
    case 0x2D:
        return TEK_LED_DIALOG;
    case 0x21:
        return TEK_LED_CAPS_LOCK;
    default:
        return TEK_LED_NONE;
    }
}
