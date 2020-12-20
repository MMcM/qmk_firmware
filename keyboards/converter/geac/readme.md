# Geac 8340

A converter for the Geac 8000 series Public Enquiry Terminal (PET) keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 8340-01, A-Star Micro  

Make example for this keyboard (after setting up your build environment):

    make converter/geac:default

The keyboard connects with to 6P6C RJ ("RJ12") modular jack. Any four GPIOs can be used.

| RJ | Color  | Signal        | Arduino | AVR |
|----|--------|---------------|---------|-----|
| 1  | White  | +5VDC         | 5V      | VCC |
| 2  | Black  | Ground        | GND     | GND |
| 3  | Red    | Key state     | 0 RXD   | PD2 |
| 4  | Green  | Jumper J2     | 2       | PD1 |
| 5  | Yellow | Address bit   | 1 TXD   | PD3 |
| 6  | Blue   | Clock         | 3       | PD0 |
