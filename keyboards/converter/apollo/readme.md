# Apollo

A converter for the Apollo Domain keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 007121, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/apollo:default

## Protocol

The keyboard protocol is 1200 baud TTL serial with even parity.
It is documented in the [Technical Reference](https://archive.org/details/bitsavers_apollo008704000TechnicalReferenceAug87_8288958/page/n141/mode/2up).

## Connections

The keyboard has a 5V regulator, so power around 8-12V is needed.

The cable from the keyboard has a DE-9 M connector (the right-hand one; the left-hand F connector is for a mouse).

| DE-9 | Signal       | AVR |
|------|--------------|-----|
| 2    | +12VDC       |     |
| 3    | RESET*       | D1  |
| 4    | TXD (to CPU) | D2  |
| 5    | RXD (to kbd) | D3  |
| 6    | GND          | GND |
| 7    | GND          | GND |

## Keys

```
+---+---+---+    +-----+-----+-----+-----+-----+   +-----+-----+-----+-----+-----+  +---+---+---+---+---+
|01 |02 |03 |    |04   |05   |06   |07   |08   |   |09   |0A   |0B   |0C   |0D   |  |0E |0F |10 |11 |12 |
+-----------+    +-+---------------------------+---+----------------------------++  +---+---+---+---+---+
|13 |14 |15 |      |17 |18 |19 |1A |1B |1C |1D |1E |1F |20 |21 |22 |23 |24 |25  |
+-----------+      +------------------------------------------------------------+       +---+---+---+---+
|27 |28 |29 |      |2C   |2D |2E |2F |30 |31 |32 |33 |34 |35 |36 |37 |38 |  |3A |       |3C |3D |3E |3F |
+-----------+   +---+----------------------------------------------------|  |---+       +---------------+
|40 |41 |42 |   |43 |7E*  |46 |47 |48 |49 |4A |4B |4C |4D |4E |4F |50 |52   |53 |       |55 |56 |57 |58 |
+-----------+   +---------------------------------------------------------------+       +---------------+
|59 |5A |5B |   |5D |5E     |60 |61 |62 |63 |64 |65 |66 |67 |68 |69 |6A     |6C |       |6E |6F |70 |   |
+-----------+   +---+-------+---+-+------------------------------+--+-------+---+       +-----------|7C |
|72 |73 |74 |                     |76                            |                      |79     |7B |   |
+---+---+---+                     +------------------------------+                      +-------+---+---+
```

`CAPS LOCK` toggles inside the keyboard and sets up / down for on / off, as though locking.
