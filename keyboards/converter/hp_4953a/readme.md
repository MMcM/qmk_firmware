# HP 4953A

A converter for the HP 4953A Protocol Analyzer keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 4953a, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/hp_4953a:default

The key address is loaded into a mux and demux and the key state of that single key read out.

## Connections

Inside the keyboard is a 20-pin IDC connector.

| J1 | Signal     | AVR |
|----|------------|-----|
|  1 | Mux C      | PB6 |
|  2 | Ground     | GND |
|  3 | Mux B      | PB5 |
|  4 | Ground     | GND |
|  5 | Mux A      | PB4 |
|  6 | Ground     | GND |
|  7 | Demux Gate | PB3 |
|  8 | Ground     | GND |
|  9 | Demux C    | PB2 |
| 10 | Ground     | GND |
| 11 | Demux B    | PB1 |
| 12 | Ground     | GND |
| 13 | Demux A    | PB0 |
| 14 | Ground     | GND |
| 15 | Mux Y      | PD0 |
| 16 | Vcc        | +5V |
| 17 | Vcc        |     |
| 18 | Vcc        | +5V |
| 19 |            |     |
| 20 |            |     |

## Keys

```
       +---+---+---+---+---+---+---+---+
       |30 |31 |33 |34 |37 |38 |39 |3B |
       +---+---+---+---+---+---+---+---+
                                                          +---+---+---+---+
                                                          |2C |2D |2E |2F |
                                                          +---+---+---+---+
  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+     +---+---+
  |20 |21 |22 |23 |24 |25 |16 |17 |18 |19 |1A |1B |1C |1D |     |4E |4F |
+-+-----------------------------------------------------+-+     +---+---+
|10 |11 |02 |03 |04 |05 |06 |07 |08 |49 |4A |5A |5B |5C |     +---+---+---+
++------------------------------------------------------++    |5D |5E |5F |
 |00 |01 |42 |43 |44 |45 |46 |57 |68 |69 |6A |6B |6C |6D |    +-----------+
 +---------------------------------------------------|   |    |6E   |6F   |
 |40   |52 |53 |54 |65 |66 |77 |78 |79 |7A |7B |7C   +---+    +-----------+
 +-----+---+---+---+---+---+---+---+---+---+---+-----+        |7D |7E |7F |
          |76                            |                    +---+---+---+
          +------------------------------+
```
