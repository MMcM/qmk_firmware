# QVT-101

A converter for the Qume QVT-101 and QVT-102 terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: QVT-101, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/qume/qvt_101:default

## Connections ##

The keyboard uses a 4P4C RJ connector. The cable is crossover, so pins are reversed on the converter side.

The (single) data line is pulled up to 12V, so some kind of level shifter is needed to bring it back down. Copying the circuit in the terminal iself from the [Maintenance Manual]() works. That circuit also allows for bidirectional data, in which case PD2/RX1 should be input from the keyboard and PD3/TX1 output to the keyboard.

| Kbd | Color  | Signal | Cvt | Color  |
|-----|--------|--------|-----|--------|
| 1   | Black  | GND    | 4   | Yellow |
| 2   | Red    | +12V   | 3   | Green  |
| 3   | Green  | PE     | 2   | Red    |
| 4   | Yellow | DATA   | 1   | Black  |

**NB**: The QVT-101+ does not have a compatible pinout. It is a 5V device.

## Keys ##

```
    +---+                                   +---+---+---+---+---+---+   +---+---+---+---+
    |2C |                                   |49 |6B |4A |4B |7B |7A |   |6A |1A |69 |19 |
    +---------------------------------------------------------------+   +---------------+
    |4E |7E |67 |47 |45 |65 |64 |44 |62 |42 |60 |40 |6C |4C |68 |48 |   |1B |0B |3B |38 |
    +---------------------------------------------------------------+   +---------------+
    |6E   |2E |27 |77 |75 |25 |24 |74 |72 |22 |20 |70 |7C |   |78 |     |58 |5A |3A |59 |
+---------------------------------------------------------+   +---+     +---------------+
|A0*|82* |1E |0E |07 |17 |15 |05 |04 |14 |12 |02 |00 |5C      |10 |     |08 |0A |39 |09 |
+-------------------------------------------------------------+---+     +-----------+   |
|5E |90*   |3E |57 |37 |35 |55 |54 |32 |52 |50 |30 |90*   |1C |         |18     |5B |   |
+---+------+---------------------------------------+------+---+         +-------+---+---+
             |34                                |
             +----------------------------------+
```

`*`: Shift keys are only sent in conjunction with another key and are handled specially.
