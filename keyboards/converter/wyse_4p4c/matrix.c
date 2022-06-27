
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

static uint16_t last_time;

void matrix_init_custom(void) {
    setPinOutput(CLOCK_PIN);
    setPinInputHigh(DATA_PIN);

    last_time = timer_read();
}

static inline uint8_t read_bits(uint8_t nbits) {
    uint8_t bits = 0;
    for (uint8_t i = 0; i < nbits; i++) {
        writePinHigh(CLOCK_PIN);
        wait_us(1);
        uint8_t val = !readPin(DATA_PIN);
        bits |= (val << i);
        wait_us(1);
        writePinLow(CLOCK_PIN);
        wait_us(1);
    }
    return bits;
}

#define SCAN_INTERVAL_MS 2

uint8_t led_count = 7;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    uint16_t now = timer_read();
    if (now - last_time < SCAN_INTERVAL_MS) {
        return false;
    }

    last_time = now;

#if defined(__AVR__)
    cli();
#elif defined(PROTOCOL_CHIBIOS)
    chSysLockFromISR();
#endif

    uint8_t matrix[18];
    for (uint8_t row = 0; row < 18; row++) {
        matrix[row] = read_bits(8);
    }

    uint8_t id = read_bits(8);

    read_bits(led_count);

#if defined(__AVR__)
    sei();
#elif defined(PROTOCOL_CHIBIOS)
    chSysUnlockFromISR();
#endif

    static bool id_printed = false;
    if (!id_printed) {
        xprintf("id = %02X\n", id);
        id_printed = true;
    }

    bool changed = false;
    for (uint8_t row = 0; row < 18; row++) {
        if (current_matrix[row] != matrix[row]) {
            current_matrix[row] = matrix[row];
            changed = true;
        }
    }    

    return changed;
}
