
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

// The SHIFT LOCK LED is automatically managed. Only the top-right unlabelled switch's is under protocol control.

void led_set(uint8_t usb_led) {
    uint8_t code;

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        code = 0xE0;
    else
        code = 0xA0;

#if defined(__AVR__)
    serial_send(code);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, &code, 1);
#endif
}
