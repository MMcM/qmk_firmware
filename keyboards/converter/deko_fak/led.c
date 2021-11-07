
#include "led.h"
#include "ps2.h"

/*
 * .---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
 * | C0| C1|  | C2|   | C3| C4| C5| C6|  | C7| C8| C9| CA|   | CB| CC|  | CD| CE|  | CF| D0|  +---+---+     +---+   +-----+
 * .-------.  .---.   .---------------.  .---------------.   .-------.  .-------.  .-------.  |   |   |     |   |   |     |
 * | D1| D2|  | D3|   | D4| D5| D6| D7|  | D8| D9| DA| DB|   | DC| DD|  | DE| DF|  | E0| E1|  +---+---+     +---+   +-----+
 * .---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
 * +---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
 * |   |   |  |   |   |   |   |   |   |  |   |   |   |   |  |   |   |   |   |  |   | EC|   |
 * +---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
 * +---+---+  +---+---+---+---+---+---+---+---+---+---+---+---+---+---------+  +---+---+---+  .---.---.  +---+---+---+---+
 * |   |   |  |   |   |   |   |   |   |   |   |   |   |   |   |   |         |  |   |   |   |  | E2| E3|  | E4|   |   |   |
 * +-------+  +-------------------------------------------------------------+  +-----------+  .-------.  +---------------+
 * |   |   |  |     |   |   |   |   |   |   |   |   |   |   |   |   |       |  |   |   |   |  | E7| E8|  |   |   |   |   |
 * +-------+  +-------------------------------------------------------------+  +---+---+---+  .---.---.  +------------   +
 * |   |   |  |    E9|   |   |   |   |   |   |   |   |   |   |   |          |      |   |      .---.---.  |   |   |   |   |
 * +-------+  +-------------------------------------------------------------+  +---+---+---+  | EA| EB|  +---------------+
 * |   |   |  |        |   |   |   |   |   |   |   |   |   |   |            |  |   |   |   |  .---.---.  |   |   |   |   |
 * +-------+  +-------------------------------------------------------------+  +-----------+  +-------+  +------------   +
 * |   |   |  |     |    |     |                           |     |    |     |  |   |   |   |  |   |   |  |       |   |   |
 * +-------+  +-----+    +---------------------------------------+    +-----+  +---+---+---+  +-------+  +---------------+
 *
 * The 3 standard LEDs support the standard PS2 0xED command for setting a lit mask.
 * Additional commands are added for all LEDs, including those, as follows:
 *  - 0xEC <led> turn on given LED, code as in the above diagram.
 *  - 0xE8 <led> start the given LED blinking.
 *  - 0xEB turn off all LEDs except the standard ones.
 *
 * The 0xEA command does not immediately cause a NAK, but does seem to reset on the argument byte.
 */

// Standard PS2 LEDs
void led_set(uint8_t usb_led) {
    uint8_t ps2_led = 0;
    if (usb_led &  (1<<USB_LED_SCROLL_LOCK))
        ps2_led |= (1<<PS2_LED_SCROLL_LOCK);
    if (usb_led &  (1<<USB_LED_NUM_LOCK))
        ps2_led |= (1<<PS2_LED_NUM_LOCK);
    if (usb_led &  (1<<USB_LED_CAPS_LOCK))
        ps2_led |= (1<<PS2_LED_CAPS_LOCK);
    ps2_host_set_led(ps2_led);
}

#ifdef LED_MATRIX_ENABLE

#include "led_matrix.h"

#define LED_STATE_OFF 0
#define LED_STATE_SOLID 1
#define LED_STATE_BLINK 2

static struct {
    unsigned current:2;
    unsigned pending:2;
} led_states[DRIVER_LED_TOTAL] = { { 3, 0 } }; // To force turn off.

static void set_value(int index, uint8_t value) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        led_states[index].pending = value;
    }
}

static void set_value_all(uint8_t value) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led_states[i].pending = value;
    }
}

static void init(void) {
    set_value_all(0);
}

static void flush(void) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (led_states[i].current != LED_STATE_OFF && led_states[i].pending == LED_STATE_OFF) {
            dprintf("s%02X\n", 0xEB);
            ps2_host_send(0xEB);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                led_states[i].current = LED_STATE_OFF;
            }
        }
    }
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (led_states[i].current != led_states[i].pending) {
            uint8_t cmd = led_states[i].pending == LED_STATE_SOLID ? 0xEC : 0xE8;
            uint8_t pos = 0xC0 + i;
            dprintf("s%02X %02X\n", cmd, pos);
            if (ps2_host_send(cmd) == 0xFA) {
              ps2_host_send(pos);
            }
            led_states[i].current = led_states[i].pending;
        }
    }    
}

const led_matrix_driver_t led_matrix_driver = {
    .init  = init,
    .set_value = set_value,
    .set_value_all = set_value_all,
    .flush = flush
};

#endif
