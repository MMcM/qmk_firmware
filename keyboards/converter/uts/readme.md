# Sperry-Univac UTS

Low Profile Expanded Typewriter keyboard for UTS-10, -20, -30, and -40 systems.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Low Profile, Adafruit Itsy-bitsy 5V  

Make example for this keyboard (after setting up your build environment):

    make converter/uts:default

## Protocol

The keyboard protocol is 9600 baud TTL serial.

Each report consists of two bytes, the first of which has the high bit set and the second of which has it clear.
In general, the first byte indicates shift state, and the second byte is the scan code.
The to-keyboard direction must have sent data (any data) recently in order for the keyboard to report.

## Connections

The keyboard cable terminates in a 9-pin d-sub (DE-9).

| PCB | Color  | DE9 | Signal        |
|-----|--------|-----|---------------|
|  2  | Orange |  1  | GND           |
|  3  | Brown  |  8  | TX (to kbd)   |
|  4  | Pink   |  6  | -RX           |
|  5  | Yellow |  7  | RX (from kbd) |
|  8  | Red    |  2  | +5V           |

## Keys

```
+-----+-----+ +-----+---+---+---+---+----+----+----+----+----+----+----+-----+ +---+---+---+---+
|74   |73   | |05   |61 |60 |65 |5D |02  |0A  |3A  |0B  |43  |44  |45  |4E   | |6B |6C |6D |71 |
+-----------+ +-+--------------------------------------------------------+---+ +---------------+
|6F   |6E   |   |4A |15 |14 |2E |39 |01 |2B |46 |27 |38 |3F |1E |11 |0F  |     |66 |67 |68 |70 |
+-----------+   +--------------------------------------------------------+---+ +---------------+
|6A   |69   |   |22   |21 |23 |24 |25 |29 |26 |28 |2F |32 |20 |4D |4C |5C |  | |62 |63 |64 |5E |
+-----------+ +-+---------------------------------------------------------|  | +-----------|   |
|1F         | |82* |81*|16 |17 |18 |1C |19 |1B |1A |1D |31 |13 |12 |56 |4B   | |5F     |75 |   |
+-----------+ +---------------------------------------------------------+----+ +-------+---+---+
|0D   |10   | |80*   |5A |06 |07 |08 |09 |50 |51 |52 |04 |0C |55 |80*   |
+-----------+ +---------+-----------------------------------+-----------+
|2C         |           |2A                                 |
+-----------+           +-----------------------------------+
```

`FCTN` and `SHIFT` are handled specially and cannot generally be remapped.
