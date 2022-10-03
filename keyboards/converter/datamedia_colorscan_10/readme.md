# Colorscan 10

A converter for the Datamedia Colorscan 10 terminal keyboard. This was a clone of the VT100 with eight color capability.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: COLOR 10, DFRobot Beetle  

Make example for this keyboard (after setting up your build environment):

    make converter/datamedia_colorscan_10:default

# Protocol

The protocol seems to be roughly inspired by the VT100, with a single bidirectional open collector bit serial signal, over which the terminal constantly sends LED / beeper state and gets back key state in return. After a start bit, there are 9 bits of LED and 12 bits of any key press with its associated shift keys. The bit width is 2.5ms, so 400 baud.

The connector is an 8P8C RJ plug, but again with only three signals.

| RJ    | Colors              | Signal | AVR |
|-------|---------------------|--------|-----|
| 1,2,3 | Gray, Orange, Black | Ground | GND |
| 4,5,6 | Red, Green, Yellow  | +5V    | VCC |
| 7,8   | Black, Brown        | Data   | PD3 |
