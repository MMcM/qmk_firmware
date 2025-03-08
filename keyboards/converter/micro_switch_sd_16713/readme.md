# Micro Switch SD-16713.

A converter for keyboard assembly 87SD30-68, used in the Selenia Tina 270/78 Telex system.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: SD-16713, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/micro_switch_sd_16713:default

Keyboard has a 26-pin header.

## Connections ##

| PCB | Signal      | AVR |
|-----|-------------|-----|
|  1  | CHAR BIT 1  | PB0 |
|  2  | CHAR BIT 2  | PB1 |
|  3  | CHAR BIT 3  | PB2 |
|  4  | CHAR BIT 4  | PB3 |
|  5  | CHAR BIT 5  | PB4 |
|  6  | CHAR BIT 6  | PB5 |
|  7  | CHAR BIT 7  | PB6 |
|  8  | KEY BREAK   | PB7 |
|14,15| GND         | GND |
|16,17| +5V         | +5V |
| 22  | ACK 1       | PD0 |
| 23  | RESET       | PD1 |
| 24  | ACK 2       | PD2 |
| 25  | CHAR AVAIL  | PD3 |
| 26  | CLIK OUT    | PD4 |

## Keys ##

The board under test had to keycaps and two of the switches did not respond.

```
+---+---+   +---+---+---+---+---+---+---+---+---+---+---+---+---+------+  +---+---+   +---+---+---+
|50 |51 |   |3D |21 |22 |23 |24 |25 |26 |27 |28 |29 |20 |30 |11 |31    |  |5F |?? |   |40 |41 |42 |
+-------+   +----------------------------------------------------------+  +-------+   +-----------+
|52 |53 |   |36   |70 |76 |64 |71 |73 |78 |74 |68 |6E |6F |1B |15 |35  |  |0C |?? |   |43 |44 |45 |
+-------+   +------------------------------------------------------+---+  +-------+   +-----------+
|54?|55 |   |4C*   |60 |72 |63 |65 |66 |67 |69 |6A |6B |7E |12 |0F |08 |  |0E |13 |   |46 |47 |48 |
+-------+   +------------------------------------------------------|   |  +-------+   +-----------+
|56 |57 |   |4D* |09 |79 |77 |62?|75 |61 |6D |6C |33 |32 |14 |4E*  |   |  |16 |1A |   |49 |4A |4B |
+---+---+   +---+-------------------------------------------------+---++  +---+---+   +---+---+---+
                |34   |10                                  |4F*|18    |
                +-----+------------------------------------+---+------+
```

`*`: sends break with `80` bit set.
