# QVT-61

A converter for the Qume QVT-61 terminal keyboard, a clone of the DEC LK201 with vintage Cherry MX black switches.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: QVT-61, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/qume/qvt_61:default

## Connections ##

The keyboard uses a 4P4C RJ connector. The cable is crossover, so pins are reversed on the converter side.

| Kbd | Color  | Signal | Cvt | Color  | AVR |
|-----|--------|--------|-----|--------|-----|
| 1   | Black  | GND    | 4   | Yellow | GND |
| 2   | Red    | +5V    | 3   | Green  | VCC |
| 3   | Green  | STROBE | 2   | Red    | PD1 |
| 4   | Yellow | SIGNAL | 1   | Black  | PD0 |


## Keys ##


```
+---+---+---+---+---+  +---+---+---+---+---+  +---+---+---+---+  +---+-------+  +---+---+---+---+
|68 |E8 |18 |98 |58 |  |D8 |38 |B8 |78 |F8 |  |04 |84 |44 |C4 |  |24 |A4     |  |64 |E4 |14 |94 |
+---+---+---+---+---+  +---+---+---+---+---+  +---+---+---+---+  +---+-------+  +---+---+---+---+
  +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+    +---+---+---+  +---+---+---+---+
  |C2 |8C |4C |CC |2C |AC |6C |EC |1C |9C |0C |5C |DC |62   |    |08 |88 |48 |  |8E |4E |CE |2E |
  +---------------------------------------------------------++   +-----------+  +---------------+
  |A2   |9A |FA |B2 |5A |3A |86 |BA |8A |EA |1A |3C |BC |E2  |   |C8 |28 |A8 |  |56 |D6 |36 |F6 |
 ++------------------------------------------------------+   |   +-----------+  +---------------+
 |20*|10*|92 |DA |32 |72 |F2 |0A |4A |CA |2A |7C |FC |22 |   |       |AE |      |E6 |16 |96 |76 |
 ++--------------------------------------------------------+-+   +-----------+  +---------------+
  |40* |F4 |46 |06 |D2 |7A |52 |6A |AA |02 |82 |42 |80*    |     |EE |6E |1E |  |26 |A6 |66 |0E |
  +----+-------------------------------------------+-------+     +---+---+---+  +------------   |
       |9E  |12                                    |                            |C6     |B6 |   |
       +----+--------------------------------------+                            +-------+---+---+
```
