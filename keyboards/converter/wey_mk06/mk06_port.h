
#pragma once

#define NO_PORT 0
#define PORT_3a 0x31
#define PORT_3b 0x32
#define PORT_4 0x40
#define PORT_5 0x50
#define PORT_A 0xA0
#define PORT_B 0xB0
#define PORT_X 0xE0
#define PORT_DLINK 0xF0
#define PORT_D10 0xF1
#define PORT_D20 0xF2
#define PORT_D30 0xF3
#define PORT_D40 0xF4
#define PORT_D50 0xF5
#define PORT_D60 0xF6
#define PORT_D70 0xF7
#define PORT_D80 0xF8
#define PORT_D90 0xF9
#define PORT_DA0 0xFA
#define PORT_DB0 0xFB
#define PORT_DC0 0xFC
#define PORT_DD0 0xFD
#define PORT_DE0 0xFE

void mk06_port_activate(uint8_t portno);
void mk06_ws_activate(uint8_t ws);
