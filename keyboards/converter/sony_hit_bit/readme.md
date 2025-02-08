# Sony Hit Bit

A converter for the KBD-13 separate keyboard used with the HB-700 MSX system.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 401KBC-013-09R, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/sony_hit_bit:default

Block diagram in the [S1985 Application Manual](https://cdn.preterhuman.net/texts/computing/msx/S1985.pdf), pg. 16. Pinouts, waveforms, and schematic can be found in the [Service Manual](https://archive.org/details/sonyhbf700psm/page/n59/mode/2up). Similar keyboards are described [here](https://www.msx.org/wiki/13-pin_keyboard_connector).

## Connections

Uses a DIN-13 connector. Four of the data lines are bidirectional; an additional signal determines direction.

| DIN | Signal | AVR |
|-----|--------|-----|
|  1  | /KANA  | PC6 |
|  2  | /CAPS  | PC7 |
|  3  | /X0    | PB0 |
|  4  | /X1    | PB1 |
|  5  | /X2    | PB2 |
|  6  | /X3    | PB3 |
|  7  | /X4,YD | PB4 |
|  8  | /X5,YC | PB5 |
|  9  | /X6,YB | PB6 |
| 10  | /X7,YA | PB7 |
| 11  | KBDIR  | PD0 |
| 12  | +5V    | VCC |
| 13  | GROUND | GND |

## Keys

```
+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+      | \-------/ |
|65   |66   |67   |70   |71   |     |81   |82   |83   |74   |      |  \ 85  /  |
+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+      |84 >---< 87|
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+      |  / 86  \  |
|72 |01 |02 |03 |04 |05 |06 |07 |10 |11 |00 |12 |13 |14 |75 |      | /-------\ |
+-----------------------------------------------------------+   +---------------+
|73   |46 |54 |32 |47 |51 |56 |52 |36 |44 |45 |15 |16 |77   |   |A2 |A3 |A4 |92 |
+-----------------------------------------------------|     |   +---------------+
|61    |26 |50 |31 |33 |34 |35 |37 |40 |41 |17 |20 |21 |    |   |97 |A0 |A1 |90 |
+-----------------------------------------------------------+   +---------------+
|60      |57 |55 |30 |53 |27 |43 |42 |22 |23 |24 |25 |60    |   |94 |95 |96 |A5 |
+----+---------------------------------------------------+--+   +---------------+
     |63   |62 |80                             |64   |76 |      |93 |A7 |A6 |91 |
     +-----+---+-------------------------------+-----+---+      +---+---+---+---+
```
