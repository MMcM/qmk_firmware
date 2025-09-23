# ADDS ASCII

ADDS ASCII keyboard in ADDS Mode.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: ADDS ASCII, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/adds_ascii:default

## Protocol

The PCB has a series of jumpers to select between PC/AT mode and ADDS mode.

When ADDS mode is selected, the AT DATA line is always pulled low and the RESET line is not connected. Only the AT CLOCK line does anything.

The protocol requires the terminal to strobe the signal line periodically and the keyboard then sends 8 bits of scan code, MSB-first, with a long pulse for 1 and a short pulse for 0. The scan codes are based on ASCII characters, but unchanged by shift state. Only a few keys send separate up transition codes.

## Connections

The keyboard cable goes from J1 on the PCB to a 6P6C RJ plug.

Connections for PC/AT mode (for instance, using Soarer's) are also shown here, although the additional lines do not need to be connected for this converter to work.

| J1 | Color  | RJ | PC/AT | ADDS   | AVR |
|----|--------|----|-------|--------|-----|
|  1 | White  |  5 | Vcc   | Vcc    | +5V |
|  2 | Black  |  4 | Gnd   | Gnd    | GND |
|  3 | Yellow |  1 | Clock | Signal | PD1 |
|  4 | Black  |  6 | PE    | Gnd    | GND |
|  5 | Green  |  2 | Data  | Low    | PD0 |
|  6 | Red    |  3 | Reset | N/C    | PB7 |

## Key codes

```
+---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
|1D | |23 |24 |25 |26 |28 |29 |2A |2B |3A |3C |3E |3F |40 |5E |5F |61 | |01 |62 |63 |0C |
+---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
+---+    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+
|1E |    |1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |2D |3D |60 |08 |  |0A |15 |06 |1A |
+---+  +-+-----------------------------------------------------------+  +---------------+
|1F |  |09     |51 |57 |45 |52 |54 |59 |55 |49 |4F |50 |5B |5D |   |    |07 |0B |0E |0F |
+---+ ++-------------------------------------------------------|   |    +---------------+
|21 | |02 |03   |41 |53 |44 |46 |47 |48 |4A |4B |4C |3B |27 |0D    |    |10 |11 |12 |13 |
+---+ +------------------------------------------------------------+--+ +---------------+
|22 | |04 |05     |5A |58 |43 |56 |42 |4E |4D |2C |2E |2F |05     |5C | |14 |16 |17 |1C |
+---+ +---+-------+-+-----------------------------------+-+-------+---+ +-----------|   |
                    |20                                 |               |18     |19 |   |
                    +-----------------------------------+               +-------+---+---+
```

Break codes:

```
+---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
|   | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   |   |
+---+ +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ +---+---+---+---+
+---+    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+
|   |    |64 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |   |   |   |   |
+---+  +-+-----------------------------------------------------------+  +---------------+
|   |  |       |   |   |   |   |   |   |   |   |   |   |   |   |   |    |   |   |   |   |
+---+ ++-------------------------------------------------------|   |    +---------------+
|   | |65 |     |   |   |   |   |   |   |   |   |   |   |   |      |    |   |   |   |   |
+---+ +------------------------------------------------------------+--+ +---------------+
|   | |66 |67     |   |   |   |   |   |   |   |   |   |   |67     |   | |   |   |   |   |
+---+ +---+-------+-+-----------------------------------+-+-------+---+ +-----------|   |
                    |                                   |               |       |   |   |
                    +-----------------------------------+               +-------+---+---+
```
