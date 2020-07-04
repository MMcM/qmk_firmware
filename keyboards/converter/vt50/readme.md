# VT50

A converter for the VT50 / VT50H / VT52 terminal keyboards.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: VT50, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/vt50:default

# Hardware

See [VT50 Print Set](http://bitsavers.org/pdf/dec/terminal/vt50/VT50-print-set.pdf) for the keyboard schematics. A key code is loaded into the `AC` lines and then the state of that key is read from `KEY UP H`.

The `BREAK` key is available directly.

The VT50H uses pin 11 on the connector for another `AC` bit. VT50 uses this as the `CTRL` key.

| P1  | Color  | Signal    | AVR |
|-----|--------|-----------|-----|
| 1   | Black  | +5V       | Vcc |
| 2   | Brown  | KEY UP H  | B7  |
| 3   | Red    | GND       | GND |
| 4   | Orange | AC 5      | B5  |
| 5   | Yellow | AC 4      | B4  |
| 6   | Green  | AC 3      | B3  |
| 7   | Blue   | AC 2      | B2  |
| 8   | Violet | AC 1      | B1  |
| 9   | Gray   | AC 0      | B0  |
| 10  | White  | BRK KEY L | C7  |
| 11  | Blue   | CTR KEY L | C6  |
| 11  | Black  | AC 6      | B6  |
