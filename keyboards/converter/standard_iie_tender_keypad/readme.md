# Standard IIe Tender Keypad

A converter for the Track House standard IIe tender keypad.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KPD-010, Teensy LC

Make example for this keyboard (after setting up your build environment):

    make converter/standard_iie_tender_keypad:default

## Hardware

A DB-25 connector is wired to a PCB with a 26-pin header and a matrix of switches.

| DB | AMP | LC | MCU | Matrix |
|----|-----|----|-----|--------|
|  1 |  20 |  0 | B16 | Col 0  |
|  2 |  16 |    |     |        |
|  3 |   5 |  1 | B17 | Col 1  |
|  4 |   4 |  2 | D0  | Col 2  | 
|  5 |  11 |  3 | A1  | Col 3  |
|  6 |  22 |    |     |        |
|  7 |   7 |  4 | A2  | Row 0  |
|  8 |  20 |    |     |        |
|  9 |  18 |    |     |        |
| 10 |  19 |    |     |        |
| 11 |  15 |    |     |        |
| 12 |   6 |    |     |        |
| 13 |   1 |  5 | D7  | Row 1  |
| 14 |   2 |  6 | D4  | Col 4  |
| 15 |   3 |  7 | D2  | Col 5  |
| 16 |     |    |     |        |
| 17 |     |    |     |        |
| 18 |   8 |    |     |        |
| 19 |   9 |    |     |        |
| 20 |     |    |     |        |
| 21 |  16 |  8 |  D3 | Row 2  |
| 22 |  17 |  9 |  C3 | Row 3  |
| 23 |  10 | 10 |  C4 | Row 4  |
| 24 |  21 | 11 |  C6 | Col 6  |
| 25 |  14 | 12 |  C7 | Col 7  |

## Keys

```
+---+---+---+---+   +---+---+
|24 |1  |1  |5  |   |1  |21 |
|21 |13 |23 |13 |   |7  |1  |
+---------------+   +-------+
|5  |15 |3  |5  |   |21 |22 |
|22 |13 |13 |21 |   |15 |1  |
+---------------+   +-------+
|15 |3  |4  |3  |   |25 |25 |
|22 |22 |22 |21 |   |21 |13 |
+---------------+   +-------+
|3  |4  |5  |21 |   |14 |13 |
|23 |23 |23 |4  |   |23 |14 |
+-----------|   |   +-------+
|15     |4  |   |   |21     |
|23     |13 |   |   |14     |
+---------------+   +-------+
```
