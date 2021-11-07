
#include "quantum.h"
#include "ps2.h"

/*
 * Additional PS2 commands for controlling the VFD:
 *  - 0xE5 <pos> set (linear) cursor position
 *  - 0xE6 <ch> output character
 *  - 0xE7 <ch> output extended character (only needed if 8-bit isn't working)
 *  - 0xE4 <inst> execute HD44780 instruction (clear, home, entry-mode, display-on/off, cursor/display shift) -- see CU20025ECPB-W1J data sheet at https://media.digikey.com/pdf/Data%20Sheets/Noritake%20PDFs/CU20025ECPB-W1J.pdf.
 *
 * The virtual serial port implements a subset of the Matrix-Orbital protocol, along the lines of https://learn.adafruit.com/usb-plus-serial-backpack/command-reference.
 */

#ifdef VIRTSER_ENABLE
#include "virtser.h"

#define WIDTH 20
#define HEIGHT 2

static uint8_t x_position = 0;
static uint8_t y_position = 0;

static uint8_t cursor_mode = 0;

// NOTE: If space is very tight, it is possible to turn off the bigger pieces of this emulation and still have a display good enough for many tools.
// Each of these optional features is around .5K; without either one, about 1.1K is saved.

#ifndef CUSTOM_CHAR_COMMANDS
#define CUSTOM_CHAR_COMMANDS 1
#endif

#if CUSTOM_CHAR_COMMANDS
#define CUSTOM_BANKS 5
#define CUSTOM_CHARS 8
#define CUSTOM_HEIGHT 8

static uint8_t saved_custom_chars[CUSTOM_BANKS][CUSTOM_CHARS][CUSTOM_HEIGHT] = { };
#endif

#ifndef AUTO_TEXT
#define AUTO_TEXT 1
#endif

#if AUTO_TEXT
static uint8_t display_contents[WIDTH*HEIGHT] = { 0 };

static bool auto_line_wrap = true;
static bool auto_scroll = true;
#endif

static bool send_and_check_ack(uint8_t data) {
    if (ps2_host_send(data) == 0xFA) {
        return true;
    } else {
        dprintf("??\n");
        return false;
    }
}

void virtser_recv(const uint8_t ch) {
    static enum {
        NORMAL, PREFIX, POSITION_1, POSITION_2, GPIO_OFF, GPIO_ON,
#if CUSTOM_CHAR_COMMANDS
        CREATE_CUSTOM_ADDR, CREATE_CUSTOM_CHAR, SAVE_CUSTOM_BANK, SAVE_CUSTOM_ADDR, SAVE_CUSTOM_CHAR, LOAD_CUSTOM_BANK,
#endif
        IGNORE
    } state = NORMAL;
    static uint8_t state_count;

#if CUSTOM_CHAR_COMMANDS
    static uint8_t custom_bank, custom_char;
    static uint8_t custom_pixels[CUSTOM_HEIGHT];
#endif
    
    enum {
        NONE, COMMAND, COMMAND_ARG, PARTIAL,
        GOTO_POSITION, COMMAND_THEN_GOTO_POSITION, REPAINT_AFTER_SCROLL,
#if CUSTOM_CHAR_COMMANDS
        CREATE_CUSTOM, LOAD_CUSTOM
#endif
    } action = NONE;
    uint8_t command = 0x00;
    uint8_t arg = 0x00;
    if (state == NORMAL) {
        if (ch == 0xFE) {
            state = PREFIX;
            action = PARTIAL;
        } else {
            command = 0xE6;
            arg = ch;
            action = COMMAND_ARG;
#if AUTO_TEXT
            if (x_position < WIDTH && y_position < HEIGHT) {
                display_contents[y_position * WIDTH + x_position] = ch;
            }
            x_position++;
            if (auto_line_wrap && x_position >= WIDTH) {
                action = COMMAND_THEN_GOTO_POSITION;
                x_position = 0;
                y_position++;
                if (y_position >= HEIGHT) {
                    if (auto_scroll) {
                        for (uint8_t i = 0; i < WIDTH*HEIGHT; i++) {
                            // Shift up over one line and blank bottom line.
                            display_contents[i] = i < WIDTH*(HEIGHT-1) ? display_contents[i + WIDTH] : ' ';
                        }
                        y_position = HEIGHT - 1;
                        action = REPAINT_AFTER_SCROLL;
                    } else {
                        y_position = 0;
                    }
                }
            }
#endif
        }
    } else if (state == PREFIX) {
        state = NORMAL;
        command = 0xE4;
        action = COMMAND_ARG;
        switch (ch) {
        case 0x47:
            state = POSITION_1;
            action = PARTIAL;
            break;
        case 0x42:
            state_count = 1;
            state = IGNORE;     // Minutes to stay on
            arg = 0x0C;         // Display on, no cursor
            break;
        case 0x46:
            arg = 0x08;         // Display off
            break;
        case 0x48:
            x_position = y_position = 0;
            arg = 0x02;         // Home
            break;
        case 0x58:
#if AUTO_TEXT
            for (uint8_t i = 0; i < WIDTH*HEIGHT; i++) {
                display_contents[i] = ' ';
            }
#endif
            x_position = y_position = 0;
            arg = 0x01;         // Clear
            break;
        case 0x4A:              // Underline cursor on
            cursor_mode |= 0x02;
            arg = 0x0C | cursor_mode;
            break;
        case 0x4B:              // Underline cursor off
            cursor_mode &= ~0x02;
            arg = 0x0C | cursor_mode;
            break;
        case 0x53:              // Block cursor on
            cursor_mode |= 0x01;
            arg = 0x0C | cursor_mode;
            break;
        case 0x54:              // Block cursor off
            cursor_mode &= ~0x01;
            arg = 0x0C | cursor_mode;
            break;
        case 0x4C:              // Cursor back
            if (x_position > 0) {
                x_position--;
            } else {
                x_position = WIDTH - 1;
#if AUTO_TEXT
                if (auto_line_wrap) {
                    if (y_position > 0) {
                        y_position--;
                    } else {
                        y_position = HEIGHT - 1;
                    }
                }
#endif
            }
            action = GOTO_POSITION;
            break;
        case 0x4D:              // Cursor forward
            x_position++;
#if AUTO_TEXT
            if (auto_line_wrap && x_position >= WIDTH) {
                x_position = 0;
                y_position++;
                if (y_position >= HEIGHT) {
                    y_position = 0;
                }
            }
#endif
            action = GOTO_POSITION;
            break;
#if AUTO_TEXT
        case 0x43:              // Auto-line-wrap on
            auto_line_wrap = true;
            action = NONE;
            break;
        case 0x44:              // Auto-line-wrap off
            auto_line_wrap = false;
            action = NONE;
            break;
        case 0x51:              // Auto-scroll on
            auto_scroll = true;
            action = NONE;
            break;
        case 0x52:              // Auto-scroll off
            auto_scroll = true;
            action = NONE;
            break;
#endif
        case 0x56:
            state = GPIO_OFF;
            action = PARTIAL;
            break;
        case 0x57:
            state = GPIO_ON;
            action = PARTIAL;
            break;
#if CUSTOM_CHAR_COMMANDS
        case 0x4E:
            state = CREATE_CUSTOM_ADDR;
            action = PARTIAL;
            break;
        case 0xC1:
            state = SAVE_CUSTOM_BANK;
            action = PARTIAL;
            break;
        case 0xC0:
            state = LOAD_CUSTOM_BANK;
            action = PARTIAL;
            break;
#else
        case 0x4E:
            state_count = 9;
            state = IGNORE;
            action = PARTIAL;
            break;
        case 0xC1:
            state_count = 10;
            state = IGNORE;
            action = PARTIAL;
            break;
        case 0xC0:
            state_count = 1;
            state = IGNORE;
            action = PARTIAL;
            break;
#endif
        case 0xC2:
            state_count = 9;
            state = IGNORE;
            action = PARTIAL;
            break;
        case 0x50:              // Set contrast
        case 0x91:              // Set and save contrast
        case 0x98:              // Set and save brightness
        case 0x99:              // Set brightness
            state_count = 1;
            state = IGNORE;
            action = PARTIAL;
            break;
        case 0xD0:              // Set RGB
            state_count = 8;
            state = IGNORE;
            action = PARTIAL;
            break;
        case 0xD1:              // Set LCD size
            state_count = 2;
            state = IGNORE;
            action = PARTIAL;
            break;
        default:
            action = NONE;
            break;
        }
    } else if (state == POSITION_1) {
        x_position = (ch - 1) % WIDTH;
        state = POSITION_2;
        action = PARTIAL;
    } else if (state == POSITION_2) {
        y_position = (ch - 1) % HEIGHT;
        state = NORMAL;
        action = GOTO_POSITION;
    } else if (state == GPIO_ON || state == GPIO_OFF) {
        state = NORMAL;
        uint8_t mask = 1 << ch;
        if (state == GPIO_ON) {
            PORTB |= mask;
        } else {
            PORTB &= ~mask;
        }
        action = NONE;
#if CUSTOM_CHAR_COMMANDS
    } else if (state == CREATE_CUSTOM_ADDR) {
        custom_char = ch % CUSTOM_CHARS;
        state = CREATE_CUSTOM_CHAR;
        state_count = CUSTOM_HEIGHT;
        action = PARTIAL;
    } else if (state == CREATE_CUSTOM_CHAR) {
        custom_pixels[CUSTOM_HEIGHT - state_count] = ch;
        if (--state_count == 0) {
            state = NORMAL;
            action = CREATE_CUSTOM;
        } else {
            action = PARTIAL;
        }
    } else if (state == SAVE_CUSTOM_BANK) {
        custom_bank = ch % CUSTOM_BANKS;
        state = SAVE_CUSTOM_ADDR;
        action = PARTIAL;
    } else if (state == SAVE_CUSTOM_ADDR) {
        custom_char = ch % CUSTOM_CHARS;
        state = SAVE_CUSTOM_CHAR;
        state_count = CUSTOM_HEIGHT;
        action = PARTIAL;
    } else if (state == SAVE_CUSTOM_CHAR) {
        saved_custom_chars[custom_bank][custom_char][CUSTOM_HEIGHT - state_count] = ch;
        if (--state_count == 0) {
            state = NORMAL;
            action = NONE;
        } else {
            action = PARTIAL;
        }
    } else if (state == LOAD_CUSTOM_BANK) {
        custom_bank = ch % CUSTOM_BANKS;
        state = NORMAL;
        action = LOAD_CUSTOM;
#endif
    } else if (state == IGNORE) {
        if (--state_count == 0) {
            state = NORMAL;
            action = NONE;
        } else {
            action = PARTIAL;
        }
    }
    dprintf("%02X%c", ch, action == NONE ? '\n' : ' ');
    if (action == COMMAND_THEN_GOTO_POSITION) {
        dprintf("%02X %02X ", command, arg);
        if (send_and_check_ack(command)) {
            send_and_check_ack(arg);
        }
        action = GOTO_POSITION;
#if AUTO_TEXT
    } else if (action == REPAINT_AFTER_SCROLL) {
        command = 0xE4;
        arg = 0x01;             // Clear
        dprintf("%02X %02X ", command, arg);
        if (send_and_check_ack(command)) {
            send_and_check_ack(arg);
        }
        command = 0xE6;
        for (uint8_t i = 0; i < WIDTH; i++) {
            arg = display_contents[i];
            dprintf("%02X %02X ", command, arg);
            if (!send_and_check_ack(command)) {
                break;
            }
            if (!send_and_check_ack(arg)) {
                break;
            }
        }
        action = GOTO_POSITION;
#endif
#if CUSTOM_CHAR_COMMANDS
    } else if (action == CREATE_CUSTOM) {
        command = 0xE4;
        arg = 0x40 + custom_char * CUSTOM_HEIGHT; // Set CG RAM addr to start of this char
        dprintf("%02X %02X ", command, arg);
        if (send_and_check_ack(command)) {
            send_and_check_ack(arg);
        }
        command = 0xE6;
        for (uint8_t i = 0; i < CUSTOM_HEIGHT; i++) {
            arg = custom_pixels[i];
            dprintf("%02X %02X ", command, arg);
            if (!send_and_check_ack(command)) {
                break;
            }
            if (!send_and_check_ack(arg)) {
                break;
            }
        }
        action = GOTO_POSITION; // Switch back to DD RAM
    } else if (action == LOAD_CUSTOM) {
        command = 0xE4;
        arg = 0x40;             // Set CG RAM addr to zero
        dprintf("%02X %02X ", command, arg);
        if (send_and_check_ack(command)) {
            send_and_check_ack(arg);
        }
        command = 0xE6;
        for (custom_char = 0; custom_char < CUSTOM_CHARS; custom_char++) {
            for (uint8_t i = 0; i < CUSTOM_HEIGHT; i++) {
                arg = saved_custom_chars[custom_bank][custom_char][i];
                dprintf("%02X %02X ", command, arg);
                if (!send_and_check_ack(command)) {
                    break;
                }
                if (!send_and_check_ack(arg)) {
                    break;
                }
            }
        }
        action = GOTO_POSITION; // Switch back to DD RAM
#endif
    }
    if (action == GOTO_POSITION) {
        command = 0xE4;
        arg = 0x80 + 0x40 * y_position + x_position;
        action = COMMAND_ARG;
    }
    if (action == COMMAND) {
        dprintf("%02X\n", command);
        send_and_check_ack(command);
    } else if (action == COMMAND_ARG) {
        dprintf("%02X %02X\n", command, arg);
        if (send_and_check_ack(command)) {
            send_and_check_ack(arg);
        }
    }
}

#endif
