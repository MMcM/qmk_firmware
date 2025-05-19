# Wang

A converter for the Wang 724 series serial keyboards.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 729-2042-US, 725-3488-US, AStar Micro  

Make example for this keyboard (after setting up your build environment):

    make converter/wang:default

## Protocol

The keyboard protocol is 62.5 baud TTL serial, with two stop bits.

## Connections

Earlier versions have a cable between the PCB and a DIN-4 connector.

See [4200 VS Maintenance Manual](https://archive.org/details/bitsavers_wangperiph21302Wang42104220VSWorkstationMaintenanc_17260916/page/2-8/mode/2up) and [Professional Computer Technical Reference](https://archive.org/details/bitsavers_wangprofesefMan1985_25910522/page/n47/mode/2up).

| PCB | Color  | DIN | Signal        | AVR |
|-----|--------|-----|---------------|-----|
|   1 | Green  |     | Speaker -     |     |
|   2 | Blue   |     | Speaker +     |     |
|   3 | Black  |  1  | Ground        | GND |
|   4 | Yellow |  2  | SI (to kbd)   | TX  |
|   5 | Red    |  4  | Vcc           | +5V |
|   6 | White  |  3  | SO (from kbd) | RX  |

Later versions have an internal cable from the PCB to an RJ 6P6C jack and a 6P4C external coiled cable.

See Keyboard Connector `J5` in the [4230A Maintenance Manual](https://archive.org/details/bitsavers_wangperiph217094230AWorkstationMaintenance19860317_5908130/page/n119/mode/2up).

| PCB | Color  | RJ6 | Color  | RJ4  | Signal        | AVR |
|-----|--------|-----|--------|------|---------------|-----|
|   1 | Yellow |   2 | Yellow | 2(B) | Vcc           | +5V |
|   2 | Green  |   3 | White  | 3(R) | Ground        | GND |
|   3 | Red    |   4 | Black  | 4(G) | SO (from kbd) | RX  |
|   4 | Black  |   5 | Red    | 5(Y) | SI (to kbd)   | TX  |
|   5 | White  |   6 |        |      | Ground        |     |
|   6 | Blue   |   1 |        |      | Ready         |     |
|   7 | Yellow |     |        |      | Speaker +     |     |
|   8 | Blue   |     |        |      | Speaker -     |     |

**Note**: the same internal wiring is used for AT-compatible PC keyboards, as described [here](http://sandy55.fc2web.com/keyboard/wang_724.html), with an RJ to DIN-5 180° external coiled cable. Plugging this cable into a serial keyboard will ground the clock signal, hanging up the AT protocol.

| PCB | Color  | RJ6 | Color  | DIN  | Signal        |
|-----|--------|-----|--------|------|---------------|
|   1 | Yellow |   2 | Red    |   5  | Vcc           |
|   2 | Green  |   3 | Black  |   4  | Ground        |
|   3 | Red    |   4 |        |      |               |
|   4 | Black  |   5 | Green  |   2  | Data          |
|   5 | White  |   6 | Yellow |   1  | Clock         |
|   6 | Blue   |   1 |        |      |               |
|   7 | Yellow |     |        |      | Speaker +     |
|   8 | Blue   |     |        |      | Speaker -     |

Some keyboards have a second RJ 10P10C jack for some kind of input device that can generate arrow keys and `CANCEL` and `EXEC`.

## Keys

See https://archive.org/details/bitsavers_wangprofesefMan1985_25910522/page/n43/mode/2up for very similar ISO variants.

```
  +----+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +----+
  |36  |  |7E |7D |7C |7B |  |7A |79 |78 |77 |  |76 |75 |74 |73 |  |72 |71 |70 |11 |  |12  |
  +----+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +----+

+---+---+---+---+---+---+---+---+---+---+---+---+---+--------+  +---+---+---+  +---+---+---+---+
|20 |6E |6D |6C |6B |6A |69 |68 |67 |66 |65 |2F |64 |2B      |  |53 |62 |61 |  |60 |13 |14 |18 |
+------------------------------------------------------------+  |   |-------+  +---------------+
|6F   |5F |5E |5D |5C |5B |5A |59 |58 |57 |56 |55 |21 |54 |  |  |   |52 |51 |  |50 |15 |16 |19 |
+------------------------------------------------------------+  +---+---+---+  +---------------+
|1E    |4F |4E |4D |4C |4B |4A |49 |48 |47 |46 |45 |44       |      |29 |      |41 |40 |17 |1A |
+------------------------------------------------------------+  +---+---+---+  +---------------+
|1B      |3F |3E |3D |3C |3B |3A |39 |38 |2A |37 |35     |23 |  |2D |26 |2E |  |31 |30 |10 |1C |
+--+-----------------------------------------------+---------+  +---+---+---+  +-----------|   |
   |33 |24 |2C                                 |25 |                |28 |      |34     |32 |   |
   +---+---+-----------------------------------+---+                +---+      +-------+---+---+
```
