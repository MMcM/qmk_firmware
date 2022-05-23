
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "quantum.h"
#include "timer.h"

#if defined PROTOCOL_CHIBIOS
#include "hal.h"
#else
#error Only support 32-bit MCUs
#endif

static matrix_row_t matrix[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

#include "mk06_port.h"

__attribute__ ((weak))
void mk06_port_activate(uint8_t portno) {
}

__attribute__ ((weak))
void mk06_ws_activate(uint8_t ws) {
}

#ifndef HOST_PORT
#define HOST_PORT NO_PORT
#endif
#ifndef DLINK_PORT
#define DLINK_PORT NO_PORT
#endif

#ifndef SD1_PORT
#define SD1_PORT NO_PORT
#endif
#ifndef SD2_PORT
#define SD2_PORT NO_PORT
#endif
#ifndef SD3_PORT
#define SD3_PORT NO_PORT
#endif

#if !SD1_PORT && !SD2_PORT && !SD3_PORT
#error No port connection defined
#endif

static uint8_t current_led = 0;

void mk06_set_led(uint8_t led) {
    current_led = led;
}

typedef enum { IDLE, MAKE, BREAK, HOST, DLINK } mk06_port_state_t;

typedef struct {
    uint8_t portno;
    const char *name;
    SerialDriver *sdp;
    mk06_port_state_t state;
} mk06_port_t;

#if SD1_PORT
static mk06_port_t sd1_port;
#endif
#if SD2_PORT
static mk06_port_t sd2_port;
#endif
#if SD3_PORT
static mk06_port_t sd3_port;
#endif

static void mk06_port_init(mk06_port_t *port, uint8_t portno, SerialDriver *sdp) {
    port->portno = portno;
    switch (portno) {
    case PORT_3a:
        port->name = "P3a";
        break;
    case PORT_3b:
        port->name = "P3b";
        break;
    case PORT_4:
        port->name = "P4";
        break;
    case PORT_5:
        port->name = "P5";
        break;
    case PORT_A:
        port->name = "HPA";
        break;
    case PORT_B:
        port->name = "HPB";
        break;
    case PORT_X:
        port->name = "Ext";
        break;
    default:
        port->name = "???";
        break;
    }
    port->sdp = sdp;
#if HOST_PORT
    if (portno == HOST_PORT) {
        port->state = HOST;
        return;
    }
#endif
#if DLINK_PORT
    if (portno == DLINK_PORT) {
        port->state = DLINK;
        return;
    }
#endif
    port->state = IDLE;
}

static void mk06_port_active(uint8_t portno) {
    static uint8_t active = NO_PORT;
    if (active != portno) {
        active = portno;
        mk06_port_activate(portno);
    }
}

static void host_recv(mk06_port_t *port, uint8_t data) {
    static enum {
        IDLE, MAKE, BREAK, WORKSTATION
    } state = IDLE;
    bool begin = false, end = false;

    switch (state) {
    case IDLE:
        begin = true;
        switch (data) {
        case 0x20:
            state = MAKE;
            break;
        case 0x21:
            state = BREAK;
            break;
        case 0x22:
            state = WORKSTATION;
            break;
        case 0x7F:
        case 0xC0:
            // Just suppress end.
            break;
        default:
            end = true;
            break;
        }
        break;

    case MAKE:
    case BREAK:
        // data is scan code set 3, mostly.
        state = IDLE;
        end = true;
        break;

    case WORKSTATION:
        mk06_ws_activate(data + 1);
        state = IDLE;
        end = true;
        break;
    }

    if (debug_enable) {
        if (begin) {
            xprintf("%s>", port->name);
        }
        xprintf(" %02X", data);
        if (end) {
            println();
        }
    }
}

static void dlink_mouse(uint8_t addr, const uint8_t *mouse) {
#ifdef MOUSE_ENABLE
    report_mouse_t mouse_report;
    mouse_report.buttons = 0;
    if ((mouse[0] & 0x20) != 0) {
        mouse_report.buttons |= 1; // left button
    }
    if ((mouse[0] & 0x10) != 0) {
        mouse_report.buttons |= 2; // right button
    }
    if ((mouse[3] & 0x20) != 0) {
        mouse_report.buttons |= 4; // middle button
    }
    if ((mouse[3] & 0x10) != 0) {
        mouse_report.buttons |= 8; // fourth button
    }
    // x, y bytes seem to always have high bits zero and those bits appear earlier instead.
    mouse_report.x = mouse[1] | ((mouse[0] & 0x03) << 6);
    mouse_report.y = mouse[2] | ((mouse[0] & 0x0C) << 4);
    mouse_report.v = mouse[3] & 0x0F;
    if (mouse_report.v & 0x08) {
        mouse_report.v |= 0xF0; // sign extend
    }
    mouse_report.v = -mouse_report.v; // direction reversed
    mouse_report.h = 0;
    host_mouse_send(&mouse_report);
#endif
}

static const uint8_t led_cmds[8] = {
    0x08,                       // None
    0x14,                       // Scroll Lock
    0x12,                       // Num Lock
    0x1A,                       // Num Lock, Scroll Lock
    0x10,                       // Caps Lock
    0x15,                       // Caps Lock, Scroll Lock
    0x19,                       // Caps Lock, Num Lock
    0x1D                        // Caps Lock, Num Lock, Scroll Lock
};

static void dlink_recv(mk06_port_t *port, uint8_t data) {
    static enum {
        IDLE, MAKE, BREAK,
        MOUSE_1, MOUSE_2, MOUSE_3, MOUSE_4,
        GPIO, GPIO_OFF, GPIO_ON, GPIO_ON_2,
        IGNORE_1, IGNORE_2
    } state = IDLE;
    static uint8_t prefix_addr = 0;
    bool begin = false, end = false;

    switch (state) {
    case IDLE: {
        uint8_t addr = data & 0xF0;
        uint8_t cmd = data & 0x0F;
        if (addr == 0x00 || addr == 0xF0) {
            begin = true;
            if (data == 0xF0) {
                // F0 might be assigned VS-DEF DLINK module (how to tell?).
                state = GPIO;
                break;
            // 00 08, FF 08, FD x0 08 sent at bootup.
            } else if (data == 0x00 || data == 0xFF) {
                state = IGNORE_1;
                break;
            } else if (data == 0xFD) {
                state = IGNORE_2;
                break;
            }
            end = true;
            break;
        }
        if (cmd == 0x06) {
            // Send LED changes to all active WS, since we are only one USB keyboard.
            static uint8_t leds[16] = { 0 };
            uint8_t idx = addr >> 4;
            if (leds[idx] != current_led) {
                leds[idx] = current_led;

                uint8_t leds[3];
                leds[0] = addr;
                leds[1] = led_cmds[current_led & 7];
                leds[2] = 0x00;
                sdWrite(port->sdp, leds, 3);

                dprintf("%s< %02X %02X %02X\n", port->name, leds[0], leds[1], leds[2]);
            }
            // Do not dprint these; they are sent too often.
            return;
        }
        begin = true;
        switch (cmd) {
        case 0x00:
            state = MAKE;
            break;
        case 0x01:
            state = BREAK;
            break;
        case 0x02:
            state = MOUSE_1;
            break;
        default:
            end = true;
            break;
        }
        prefix_addr = addr;
        break;
    }

    case MAKE:
    case BREAK: {
        mk06_port_active(PORT_DLINK + (prefix_addr >> 4));
        uint8_t row = data >> 4;
        uint8_t col = data & 0x0F;
        if (state == MAKE) {
            matrix[row] |= (1 << col);
        } else {
            matrix[row] &= ~(1 << col);
        }
        state = IDLE;
        end = true;
        break;
    }

    case MOUSE_1:
        if ((data & 0x40) == 0) {
            // A0 seems to indicate fifth button.
            state = IDLE;
            end = true;
            break;
        }
    /* else falls through */
    case MOUSE_2:
    case MOUSE_3:
    case MOUSE_4: {
        static uint8_t mouse[4];
        mouse[state - MOUSE_1] = data;
        if (state == MOUSE_4) {
            dlink_mouse(prefix_addr, mouse);
            state = IDLE;
            end = true;
        } else {
            state++;
        }
        break;
    }

    case GPIO:
        switch (data) {
        case 0x81:
            state = GPIO_OFF;
            break;
        case 0x82:
            state = GPIO_ON;
            break;
        default:
            end = true;
        }
        break;
    case GPIO_OFF:
        // TODO: Turn off data bit.
        state = IDLE;
        end = true;
        break;
    case GPIO_ON:
        // TODO: Turn on data bit.
        state = GPIO_ON_2;
        break;
    case GPIO_ON_2:
        state = IDLE;
        end = true;
        break;


    case IGNORE_1:
        state = IDLE;
        end = true;
        break;
    case IGNORE_2:
        state = IGNORE_1;
        break;
    }

    if (debug_enable) {
        if (begin) {
            xprintf("%s>", port->name);
        }
        xprintf(" %02X", data);
        if (end) {
            println();
        }
    }
}

static void mk06_port_scan(mk06_port_t *port, uint8_t idx) {
    if (port->state == IDLE) {
        static uint8_t leds[3] = { 0 };
        if (leds[idx] != current_led) {
            leds[idx] = current_led;
            sdWrite(port->sdp, &current_led, 1);
            dprintf("%s< %02X\n", port->name, current_led);
        }
    }

    msg_t msg = sdGetTimeout(port->sdp, TIME_IMMEDIATE);
    if (msg < 0) {
        return;
    }
    uint8_t data = msg & 0xFF;

    switch (port->state) {
    case HOST:
        host_recv(port, data);
        return;
    case DLINK:
        dlink_recv(port, data);
        return;
    case IDLE:
        dprintf("%s> %02X", port->name, data);
        switch (data) {
        case 0x20:
            port->state = MAKE;
            break;
        case 0x21:
            port->state = BREAK;
            break;
        default:
            dprintf("\n");
            break;
        }
        return;
    case MAKE:
    case BREAK:
        dprintf(" %02X\n", data);
        break;
    default:
        return;
    }

    mk06_port_active(port->portno);
    uint8_t row = data >> 4;
    uint8_t col = data & 0x0F;
    if (port->state == MAKE) {
        matrix[row] |= (1 << col);
    } else {
        matrix[row] &= ~(1 << col);
    }
    port->state = IDLE;
}

void matrix_init(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) matrix[i] = 0;

#if SD1_PORT
#ifndef SD1_BAUD
#define SD1_BAUD 9600
#endif
    palSetPadMode(GPIOB, 16, PAL_MODE_ALTERNATIVE_3); // pin 0 / B16 / RX1 = UART0_RX
    palSetPadMode(GPIOB, 17, PAL_MODE_ALTERNATIVE_3); // pin 1 / B17 / TX1 = UART0_TX

    static const SerialConfig sd1cfg = { SD1_BAUD };
    sdStart(&SD1, &sd1cfg);
#if SD1_PORT == PORT_3a ||SD1_PORT == PORT_3b
    *(SD1.uart.s2_p) |= UARTx_S2_RXINV;
    *(SD1.uart.c3_p) |= UARTx_C3_TXINV;
#endif
    mk06_port_init(&sd1_port, SD1_PORT, &SD1);
#endif
#if SD2_PORT
#ifndef SD2_BAUD
#define SD2_BAUD 9600
#endif
    palSetPadMode(GPIOC, 3, PAL_MODE_ALTERNATIVE_3); // pin 9 / C3 / RX2 = UART1_RX
    palSetPadMode(GPIOC, 4, PAL_MODE_ALTERNATIVE_3); // pin 10 / C4 / TX2 = UART1_TX

    static const SerialConfig sd2cfg = { SD2_BAUD };
    sdStart(&SD2, &sd2cfg);
#if SD2_PORT == PORT_3a ||SD2_PORT == PORT_3b
    *(SD2.uart.s2_p) |= UARTx_S2_RXINV;
    *(SD2.uart.c3_p) |= UARTx_C3_TXINV;
#endif
    mk06_port_init(&sd2_port, SD2_PORT, &SD2);
#endif
#if SD3_PORT
#ifndef SD3_BAUD
#define SD3_BAUD 9600
#endif
    palSetPadMode(GPIOD, 2, PAL_MODE_ALTERNATIVE_3); // pin 7 / D2 / RX3 = UART2_RX
    palSetPadMode(GPIOD, 3, PAL_MODE_ALTERNATIVE_3); // pin 8 / D3 / TX3 = UART2_TX

    static const SerialConfig sd3cfg = { SD3_BAUD };
    sdStart(&SD3, &sd3cfg);
#if SD3_PORT == PORT_3a ||SD3_PORT == PORT_3b
    *(SD3.uart.s2_p) |= UARTx_S2_RXINV;
    *(SD3.uart.c3_p) |= UARTx_C3_TXINV;
#endif
    mk06_port_init(&sd3_port, SD3_PORT, &SD3);
#endif

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
#if SD1_PORT
    mk06_port_scan(&sd1_port, 0);
#endif    
#if SD2_PORT
    mk06_port_scan(&sd2_port, 1);
#endif    
#if SD3_PORT
    mk06_port_scan(&sd3_port, 2);
#endif    

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void) {
    print("\nr/c 012345678ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}
