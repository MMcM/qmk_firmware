# Panasonic KX-T96145

A converter for the Panasonic KX-T96145 PBX keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KX-T96145, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/panasonic_kx_t96145:default

This keyboard uses two ganged shift registers driving sixteen column diodes and reads out for rows.

## Connections

The cable ends in a DIN-13. The PCB has a 9-pin Molex-style connector.
The PCB connector is not labeled as to numbering direction; this is left-to-right when the keyboard
is in the ordinary orientation so that it is at the front of the PCB.

| PCB | DIN | Color  | Signal | AVR |
|-----|-----|--------|--------|-----|
|     |  13 | Black  | Ground | GND |
|     |  11 | Green  | PE     |     |
|   1 |   6 | Gray   | CLK    | PD0 |
|   2 |   2 | Red    | B      | PD1 |
|   3 |   3 | White  | +5V    | VCC |
|   4 |  10 | Yellow | Ground | GND |
|   5 |   4 | Orange | LED-   | PC7 |
|   6 |   8 | Pink   | ROW 1  | PB0 |
|   7 |   7 | Black  | ROW 2  | PB1 |
|   8 |   1 | Brown  | ROW 3  | PB2 |
|   9 |   5 | Blue   | ROW 4  | PB3 |

Note: `LED+` is connected to Vcc, making the signal active low.
It is best to put a small resistor (220Ω or so) between the LED GPIO and the `LED-` pin to limit current.

## Keys

```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----+---+
|00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |0A |0B |0C |0D |0E   |0F |
+-----------------------------------------------------------------+
|10   |11 |12 |13 |14 |15 |16 |17 |18 |19 |1A |1B |1C |1D |1E |1F |
+-----------------------------------------------------------------+
|20    |21 |22 |23 |24 |25 |26 |27 |28 |29 |2A |2B |2C    |2D |2E |
+-----------------------------------------------------------------+
|30      |31 |33 |34 |35 |36 |37 |39 |3A |3B |3C |30      |3F |2F |
+--------+-------------------------------------------+----+---+---+
         |32 |38                             |3D |3E |
         +---+-------------------------------+---+---+
```
