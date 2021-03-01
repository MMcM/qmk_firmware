
#include "stdint.h"
#include "led.h"

#if defined(__AVR__)
#include <avr/io.h>
#include "protocol/serial.h"
#elif defined PROTOCOL_CHIBIOS
#include "hal.h"
#endif

// These two are complements of one another; bit on means LOCAL.
#define PERICOM_LED_LOCAL (1<<0)
#define PERICOM_LED_ONLINE (1<<0)
#define PERICOM_LED_KBD_LOCKED (1<<1)
#define PERICOM_LED_L1 (1<<2)
#define PERICOM_LED_L2 (1<<3)
#define PERICOM_LED_L3 (1<<4)
#define PERICOM_LED_L4 (1<<5)
#define PERICOM_LED_L5 (1<<6)

// Transducer keep going as long as the high bit is set.
#define PERICOM_BEEP (1<<7)

void led_set(uint8_t usb_led) {
    uint8_t leds = 0;

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        leds |= PERICOM_LED_L1;

    // USB_LED_CAPS_LOCK is already covered by its own LED under the key cap.
    // There is no way to synchronize this state should another keyboard change it.
    // Also, the power-on state is CAPS LOCK on (the appropriate make code is sent).

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        leds |= PERICOM_LED_L4;     // Wait
    if (usb_led & (1<<USB_LED_COMPOSE))
        leds |= PERICOM_LED_L3;     // Compose
    if (usb_led & (1<<USB_LED_KANA))
        leds |= PERICOM_LED_L5;     // Print

#if defined(__AVR__)
    serial_send(leds);
#elif defined PROTOCOL_CHIBIOS
    sdWrite(&SD1, &leds, 1);
#endif
}
