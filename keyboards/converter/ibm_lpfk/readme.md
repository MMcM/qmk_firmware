# IBM LPFK

A converter for the IBM Lighted Program Function Keyboard.

Each key has a green LED which can also be controlled.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: IBM LPFK, Teensy LC

Make example for this keyboard (after setting up your build environment):

    make converter/ibm_lpfk:default

The protocol is described in [IBM LPFK on a Serial Port](https://www.brutman.com/IBM_LPFK/IBM_LPFK.html).

## Hardware

The protocol is 9600 baud serial at RS-232 levels, so a serial level shifter like the MAX232 is needed (there is one inside the keyboard itself).

The keyboard connects with a mini-DIN-8 cable. At least some of the cables that come with these mirror reverse the signals in each row of the connector.

A cable such as that will have the staggered pin in the middle row (5) connected to the opposite pin in that same row (3). Check this and for a straight-through cable connect to match the PCB / keyboard DIN conector. And for one that is reversed, according to the Reversed column.

| Color  | PCB | Reversed | Signal        |
|--------|-----|----------|---------------|
| Brown  | 1   | 2        | Ground        |
| Red    | 2   | 1        | Ground        |
| Orange | 3   | 5        | +5V           |
| Yellow | 4   | 4        |               |
| Green  | 5   | 3        | TX (from kbd) |
| Blue   | 6   | 8        | RX (to kbd)   |
| Violet | 7   | 7        |               |
| Gray   | 8   | 6        |               |
