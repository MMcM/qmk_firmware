# NMB 110695

A converter for the NMB Hi-Tek 725 series 110695 keyboard.
I believe that this keyboard went with a TeleVideo 9220 terminal.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: NMB 110695, Pro Micro

Make example for this keyboard (after setting up your build environment):

    make converter/nmb_110695:default

The keyboard does not send key up transitions. It does track the three shifting keys, Ctrl, Shift, and Lock, separately.

## Hardware

The keyboard protocol is 9600 baud serial. The keyboard is powered with 12VDC.

| RJ | Color  | Signal        |
|----|--------|---------------|
| 1  | White  | Reset         |
| 2  | Black  | TX (to kbd)   |
| 3  | Red    | RX (from kbd) |
| 4  | Green  | Ground        |
| 5  | Yellow | +12V          |
| 6  | Blue   | Chassis       |
