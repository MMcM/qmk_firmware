# SR100

A converter for the SRI/Century, later the Burroughs SR100.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: SR100, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/sr100:default

The keyboard does not have a microcontroller, just an Exar `22-908-03` sense amp and `22-950-3B` scan driver, which are common for Key Tronic. The open collector data bus is shared among row address, column states, and LED states.

The PCB has seven LEDs, but the case only lets six show through. The second LED (the first visible one) displays the complement of the first and does not have a separate signal. The eighth LED bit is connected to a piezo speaker, which can buzz / click if toggled at an appropriate frequency.

## Connections

The cable ends in a DA-15. The PCB has a 16-pin edge connector.

| J1 | Color       | DA | Signal              | AVR |
|----|-------------|----|---------------------|-----|
|  A |             |    |                     |     |
|  B | Yellow      |  8 | KEY 0, SEL A, LED 1 | PB0 |
|  C | Brown       |  7 | KEY 1, SEL B, LED 3 | PB1 |
|  D | Blue        |  6 | KEY 2, SEL C, LED 4 | PB2 |
|  E | Orange      |  5 | KEY 3, SEL D, LED 5 | PB3 |
|  F | Green       |  4 | KEY 4, LED 6        | PB4 |
|  H | White       |  3 | KEY 5, LED 7        | PB5 |
|  J | Red         |  2 | KEY 6, LED 8 (CAPS) | PB6 |
|  1 | Violet      |  9 | KEY 7, PIEZO        | PB7 |
|  2 | Black       | 10 | PE                  |     |
|  3 | Gray        | 11 | GROUND              | GND |
|  4 | Pink        | 12 | /LED CLK            | PD0 |
|  5 | Light Brown | 13 | /ROW DRIVER CLK     | PD1 |
|  6 | White/Black | 14 | GROUND              | GND |
|  7 | White/Red   | 15 | /SENSE RESET        | PD2 |
|  8 | Black       |  1 | +5V                 | VCC |

## Keys

```
                                                +-------+-------+       +---+---+---+---+
                                                |B0     |B1     |       |B2 |B3 |B4 |B5 |
                                                +-------+-------+       +---+---+---+---+
                                                                        |83 |B6 |B7 |06 |
    +----+                                      +---+---+---+---+---+   +---------------+
    |01  |                                      |02 |03 |04 |05 |82 |   |90 |91 |A0 |A1 |
    +----+--+---+---+---+---+---+---+---+---+---+-------------------+   +---------------+
    |70 |71 |60 |61 |50 |51 |40 |41 |30 |31 |20 |21 |10 |11 |80 |81 |   |92 |93 |A2 |A3 |
    +---------------------------------------------------------------+   +---------------+
    |72   |73 |62 |63 |52 |53 |42 |43 |32 |33 |22 |23 |12 |15 |13 |     |94 |95 |A4 |A5 |
+---+-----------------------------------------------------|   |---+     +---------------+
|74 |75    |64 |65 |54 |55 |44 |45 |34 |35 |24 |25 |14 |      |84 |     |96 |97 |A6 |A7 |
+-----------------------------------------------------------------+     +-----------|   |
|76 |77      |66 |67 |56 |57 |46 |47 |36 |37 |26 |27 |16      |17 |     |86     |87 |   |
+---+--------+-+------------------------------------------+---+---+     +-------+---+---+
               |85                                 |07    |
               +-----------------------------------+------+
```
