# Cherry 4060-A

A converter for the CGX 32-key keypad with Cherry 4060-A controller.

Each key has a red LED which can also be controlled.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Cherry 4060-A, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/cherry_4060_a:default

## Hardware

The keyboard protocol is 9600 baud serial, but with inverted logic, so an inverter must be wired between it and the
microcontroller.

| RJ | J1 | Color  | Std Color | Signal         |
|----|----|--------|-----------|----------------|
| 1  | 2  | Black  | White     | N/C            |
| 2  | 1  | Red    | Black     | +5V            |
| 3  | 4  | White  | Red       | /SI (to kbd)   |
| 4  | 3  | Green  | Green     | /SO (from kbd) |
| 5  | 5  | Yellow | Yellow    | Ground         |
| 6  | 7  | Black  | Blue      | Chassis        |
