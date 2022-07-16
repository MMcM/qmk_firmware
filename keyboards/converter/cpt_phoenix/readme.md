# CPT Phoenix

A converter for a CPT Phoenix keyboard. Might well work for the Phoenix Jr.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Phoenix; Itsy-Bitsy 5V

Make example for this keyboard (after setting up your build environment):

    make converter/cpt_phoenix:default

## Hardware

The keyboard uses a DE-9 connector. The protocol is 2400 baud TTL serial.

| DE9 | Signal        | AVR |
|-----|---------------|-----|
|  1  | Ground        | GND |
|  2  | Vcc +5V       | 5V  |
|  3  | RX (to kbd)   | TX  |
|  4  | TX (from kbd) | RX  |
|  5  | Audio         |     |
|  6  | Audio         |     |

It might work to connect to Audio to PC6 and GND.
