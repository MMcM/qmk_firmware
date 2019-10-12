# Amtelco KB163

A converter for the Amtelco KB163, an AT call center keyboard with _lots_ of vintage Cherry blacks.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KB163, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/amtelco_kb163:default

The tested hardware connection is Clock (pin 1) to XCK (D5) and Data (pin 2) to RXD (D2), in order to use the UART in synchronous mode to decode. Other arrangements, compatible with Soarer's or TMK PS2, should also work.
