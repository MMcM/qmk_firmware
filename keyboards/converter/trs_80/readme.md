# TRS-80

A converter for the TRS-80 Model 1 keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: TRS-80, Teensy 2.0++

Make example for this keyboard (after setting up your build environment):

    make converter/trs_80:default

The keyboard subassembly has a 20-pin FFC connector.

| N  | Signal | AVR |
|----|--------|-----|
|  1 | VCC    | 5V  |
|  2 | A4     | PC4 |
|  3 | A5     | PC5 |
|  4 | A1     | PC1 |
|  5 | A0     | PC0 |
|  6 | A2     | PC2 |
|  7 | A6     | PC6 |
|  8 | A7     | PC7 |
|  9 | A3     | PC3 |
| 10 | D2     | PF2 |
| 11 | D0     | PF0 |
| 12 | D5     | PF5 |
| 13 | D3     | PF3 |
| 14 | KYBD*  | PE0 |
| 15 | D6     | PF6 |
| 16 | D1     | PF1 |
| 17 | D7     | PF7 |
| 18 | D4     | PF4 |
| 19 | GROUND | GND |
| 20 | N/C    |     |
