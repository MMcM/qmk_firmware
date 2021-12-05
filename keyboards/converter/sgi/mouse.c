
#include "debug.h"
#include "print.h"

// TODO: serial_mouse support has been removed from core.
#ifdef SERIAL_MOUSE_ENABLE

#include "protocol/serial.h"

#if defined(__AVR__)

// TODO: Since this would have to use soft serial because of parity, the UART is actually available, but the routine
// names are already assigned.
#error AVR cannot have more than one serial port

#elif defined PROTOCOL_CHIBIOS

#include "hal.h"

#ifndef SD_MOUSE
#define SD_MOUSE SD2
#endif

void serial_init(void) {
#if SDSD_MOUSE == SD2
    palSetPadMode(GPIOC, 3, PAL_MODE_ALTERNATIVE_3); // pin  9 / C3 / RX2 = UART1_RX
    palSetPadMode(GPIOC, 4, PAL_MODE_ALTERNATIVE_3); // pin 10 / C4 / TX2 = UART1_TX
#else
#error Unknown keyboard serial driver
#endif

    static const SerialConfig sdcfg = { 4800 };
    sdStart(&SD_MOUSE, &sdcfg);
}

int16_t serial_recv2(void) {
    return sdGetTimeout(&SD_MOUSE, TIME_IMMEDIATE);
}

#endif

#endif
