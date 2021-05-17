
#include <stdint.h>
#include <stdbool.h>

#include "debug.h"
#include "print.h"
#include "quantum.h"

#ifdef LED_MATRIX_ENABLE

#include "led_matrix.h"

uint32_t pending_leds = 0;
uint32_t current_leds = 0;
bool led_retransmit_needed = false;

static void set_value(int index, uint8_t value) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        uint32_t mask = (uint32_t)1 << (31 -index);
        if (value) {
            if ((pending_leds & mask) == 0) {
                pending_leds |= mask;
            }
        } else {
            if ((pending_leds & mask) != 0) {
                pending_leds &= ~mask;
            }
        }
    }
}

static void set_value_all(uint8_t value) {
    if (value) {
        if (pending_leds != -1) {
            pending_leds = -1;
        }
    } else {
        if (pending_leds != 0) {
            pending_leds = 0;
        }
    }
}

static void init(void) {
    current_leds = pending_leds = 0;
    led_retransmit_needed = true;
}

static void flush(void) {
    if (current_leds == pending_leds && !led_retransmit_needed) {
        return;
    }
    current_leds = pending_leds;
    led_retransmit_needed = false;

    dprintf("LEDs: %08lX\n", pending_leds);

    uint8_t buf[5];
    buf[0] = 0x94;
    buf[1] = pending_leds >> 24;
    buf[2] = pending_leds >> 16;
    buf[3] = pending_leds >> 8;
    buf[4] = pending_leds & 0xFF;
#if defined(__AVR__)
    for (uint8_t i = 0; i < 5; i++) {
        serial_send(buf[i]);
    }
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, buf, 5);
#endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init  = init,
    .set_value = set_value,
    .set_value_all = set_value_all,
    .flush = flush
};

#endif
