# Tektronix 405x

A converter for Cherry B80-85AA used in the Tektronix 405x.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 119-0708-00, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/tektronix_4051:default

* [Theory of Operation](https://archive.org/details/bitsavers_tektronix44AServiceManualTechnicalData198211_46145022/page/n207/mode/2up)
* [Connectors](https://archive.org/details/bitsavers_tektronix44AServiceManualPartsandSchematics198305_305665166/page/n63/mode/2up)
* [Keyboard Schematic](https://archive.org/details/bitsavers_tektronix44AServiceManualPartsandSchematics198305_305665166/page/n417/mode/2up)
* [Interface Schematic](https://archive.org/details/bitsavers_tektronix44AServiceManualPartsandSchematics198305_305665166/page/n387/mode/2up)

## Connections

`J30`:

| Pin | Signal | AVR |
|-----|--------|-----|
| 1   | KCO0   | PB0 |
| 2   | KCO1   | PB1 |
| 3   | KCO2   | PB2 |
| 4   | KCO3   | PB3 |
| 5   | KCO4   | PB4 |
| 6   | KCO5   | PB5 |
| 7   | KCO6   | PB6 |
| 8   | TTY    | PF7 |

`J31`:

| Pin | Signal | AVR |
|-----|--------|-----|
| 1   | KEY    | PD3 |
| 2   | KBHALT | PC6 |
| 3   | SHIFT  | PF5 |
| 4   | CTRL   | PF6 |
| 5   | GND    | GND |
| 6   | KBCLK  | PC7 |
| 7   | +5V    | +5V |

## Keys

```
  +---+---+---+---+---+     +---+---+---+---+---+     +---+ +---+           +---+  +---+
  |60 |61 |62 |63 |64 |     |70 |71 |72 |73 |74 |     |75 | |76 |           |77 |  |6C |
  +---+---+---+---+---+     +---+---+---+---+---+     +---+ +---+           +---+  +---+
  +---+---+---+---+---+                                                            +---+
  |65 |66 |67 |68 |69 |                                                            |6D |
  +---+---+---+---+---+                                                            +---+
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+  +---+
|6A |5B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |3A |3D |5D |08 |   |7D |7F |7E |  |7C |
+-+------------------------------------------------------------++   +-----------+  +---+
  |1B |5E |51 |57 |45 |52 |54 |59 |55 |49 |4F |50 |40 |0A |0D  |    |27 |28 |29 |  |2F |
  +--------------------------------------------------------|   |    +-----------+  +---+
   |09 |90 |41 |53 |44 |46 |47 |48 |4A |4B |4C |3B |5C |5F |   |    |24 |25 |26 |  |2A |
   +-----------------------------------------------------------+    +-----------+  +---+
   |A0 |80   |5A |58 |43 |56 |42 |4E |4D |3C |3E |3F |80   |6B |    |21 |22 |23 |  |2D |
   +---+-----+---+-------------------------------+---+-----+---+    +-----------+  +---+
                 |10                             |                  |20     |2E |  |2B |
                 +-------------------------------+                  +-----------+  +---+
```
