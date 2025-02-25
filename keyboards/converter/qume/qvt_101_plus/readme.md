# QVT-101+

A converter for the Qume QVT-101+ terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: QVT-101+, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/qume/qvt_101_plus:default

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
   .---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.
   |18 |98 |58 |D8 |38 |B8 |78 |F8 |04 |84 |44 |C4 |24 |A4 |64 |E4 |
   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+---+---+
   |92 |8C |4C |CC |2C |AC |6C |EC |1C |9C |0C |5C |DC |72   |C8   |   |14 |94 |54 |D4 |
   +---------------------------------------------------------------+   +---------------+
   |52   |8E |EE |A6 |4E |2E |9E |AE |96 |F6 |0E |3C |BC |   |48   |   |EA |1A |9A |DA |
+--+-----------------------------------------------------|   |-----+   +---------------+
|88 |20*  |86 |CE |26 |66 |E6 |16 |56 |D6 |36 |7C |FC |F2    |28   |   |2A |AA |6A |7A |
+------------------------------------------------------------------+   +---------------+
|A8 |40*    |5E |1E |C6 |6E |46 |76 |B6 |02 |82 |42 |80*   |34 |32 |   |8A |4A |CA |FA |
+--+---------------------------------------------------------------+   +-----------|   |
   |08   |10*  |06                         |C2 |22 |68 |F4 |B4 |74 |   |0A     |5A |   |
   +-----+-----+---------------------------+---+---+---+---+---+---+   +-------+---+---+
```

`*`: Shift keys are only sent in conjunction with another key and are handled specially.
