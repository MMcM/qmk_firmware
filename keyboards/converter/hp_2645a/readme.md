# HP 2645A

A converter for the HP 264xx terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 02645-60023, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/hp_2645a:default

The keyboard connected to the display with a 30 position, 0.156" pitch, edge connector. A suitable male connector is available from [Digi-Key](https://www.digikey.com/products/en?keywords=ebm15mmsd).

The key switches are ITW Magnetic Valve. To generate a sense pulse, the keyboard needs both +12V and -12V. The voltage does not need to be very exact, so a boost converter from 5V works. A successful one had a part number `DD1718PA` on [AliExpress](https://www.aliexpress.com/wholesale?SearchText=DD1718PA). The 5V boost input current draw is about 500mA, so it might work to share power with the Atmega32u4. But to stay in spec, use a second USB port just for 12V. Also, if 5V is not connected, 12V will draw several times the normal current, so avoid that.

Details of how the keyboard and the part of the terminal to which it connected worked can be found in HP manual `13255-91018`, available in the [HP Museum](http://www.hpmuseum.net/document.php?hwfile=2538). An older revision is in [Bitsavers](https://archive.org/details/bitsavers_hpterminalardModuleAug76_2133416). Neither scan does a perfect job with the schematics.

## Connections for Teensy

| Pos | Signal  | MCU | Pin |
|-----|---------|-----|-----|
| A   | GND     | GND |     |
| B   | BEEP*   | PC6 |   9 |
| C   | -12V    |     |     |
| D   | CHASSIS |     |     |
| E   |         |     |     |
| F   |         |     |     |
| H   |         |     |     |
| J   | COL OUT | PF4 |  19 |
| K   | LED OUT | PF5 |  18 |
| L   |         |     |     |
| M   | RESET   | PC7 |  10 |
| N   | +5V     | VCC |     |
| P   |         |     |     |
| R   |         |     |     |
| S   | +12V    |     |     |
| 1   | +5V     | VCC |     |
| 2   | BUS0    | PB0 |   0 |
| 3   | BUS1    | PB1 |   1 |
| 4   | BUS2    | PB2 |   2 |
| 5   | BUS3    | PB3 |   3 |
| 6   | BUS4    | PB4 |  13 |
| 7   | BUS5    | PB5 |  14 |
| 8   | BUS6    | PB6 |  15 |
| 9   | BUS7    | PB7 |   4 |
| 10  | BADDR0  | PD0 |   5 |
| 11  | BADDR1  | PD1 |   6 |
| 12  | BADDR2  | PD2 |   7 |
| 13  | BADDR3  | PD3 |   8 |
| 14  | RD/COL15| PD7 |  12 |
| 15  | GND     | GND |     |

<sup>*</sup> Add a trimpot and/or resistor between `BEEP` and `PC6` to control volume; 470Ω seems about right.
