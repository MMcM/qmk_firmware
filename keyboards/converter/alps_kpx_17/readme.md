# Alps KPX-17

A converter for the Alps / Genovation KPX-17 Keypad.

There are two variants of this external keypad: serial (KPX-17S) and parallel (KPX-17P).
Each comes in two colors: black and beige.
It was also sold as the Genovation Micropad 621.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KP-17 + AStar Micro; KPX-17S + Atto; KPX-17S + Teensy LC; KPX-17P + Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/alps_kpx_17:default

## Hardware

### Direct

The Alps switch matrix is a separate PCB, labeled KP-17, with a 9-pin header.

| Pin | Signal | AVR |
|-----|--------|-----|
|  9  | Col 4  | B4  |
|  8  | Col 3  | E6  |
|  7  | Col 2  | D7  |
|  8  | Col 1  | C6  |
|  5  | Row 5  | D4  |
|  4  | Row 4  | D0  |
|  3  | Row 3  | D1  |
|  2  | Row 2  | D3  |
|  1  | Row 1  | D2  |

### Serial

The serial keypad has a standard DE-9 connector. The protocol is 1200 baud RS-232.
This needs to be converted to TTL levels, such as with a MAX3232 breakout board with an appropriate connector.
The converter uses the first hardware UART serial port.

### Parallel

The parallel keypad has a standard DB-25 parallel port connector.

| DB-25 | Signal | AVR |
|-------|--------|-----|
|  2    | Data 0 | B0  |
|  3    | Data 1 | B1  |
|  4    | Data 2 | B2  |
|  5    | Data 3 | B3  |
|  6    | Data 4 | B4  |
|  7    | Data 5 | B5  |
|  8    | Data 6 | B6  |
|  9    | Data 7 | B7  |
|  13   | Select | D0  |
|  15   | Error  | D1  |
|  18   | Ground | GND |

## Firmware Variants

* `direct_astar` for KP-17 + ATMega32U4

* `serial_atto` for KPX-17S + ATMega32U4

* `serial_teensy_lc` for KPX-17S + Teensy LC

* `parallel_teensy_20` for KPX-17P + ATMega32U4
