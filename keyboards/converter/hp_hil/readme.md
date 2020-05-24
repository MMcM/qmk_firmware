# HP HIL

A converter for a HP HIL keyboard and similar devices.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 46021A (keyboard), 46060A (3-button mouse), 46060B (2-button mouse), 46084A (ID module), 46086A (32-button control box), 98203C (keyboard), M1309A (3-button trackball), Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/hp_hil:default

## Hardware

HIL is a multi-device protocol like USB or ADB. It is described in detail in [HP-HIL Technical Reference Manual](http://bitsavers.trailing-edge.com/pdf/hp/hp-hil/45918A-90001_HP-HIL_Technical_Reference_Manual_Jan86.pdf).

The chain of devices attaches with an "E" keyed 4-pin SDL connector from ~~AMP~~ ~~Tyco~~ TE Connectivity, [5-1761185-1](https://www.digikey.com/product-detail/en/te-connectivity-amp-connectors/5-1761185-1/5-1761185-1-ND/).

Devices need 12V (even though they all immediately regulate it down to 5V).

| SDL | AVR   | Signal |
|-----|-------|--------|
| 1   | N/C   | +12V   |
| 2   | D2 RX | SI     |
| 3   | D3 TX | SO     |
| 4   | GND   | Ground |

## Features

* A single layout includes keys from both the normal keyboard (key code set 1) and the 32-button control box (key code set 2).
* Both two- and three-button mice are supported.
* Backlight is mapped to the general prompt / acknowledge, which is the single LED in the corner on the 32-button control box.
  * This could be used to indicate a layer, for instance.
* The `I` magic command will print the security code report for devices that support it, one at a time.
  * The security code is really just the serial number.
  * The 46084A ID Module is effectively a device with a serial number and nothing else.
  * Other devices claim to support this command but return empty, presumably because their serial number is only on the label, not programmed in.

### Not yet tested

* Control dials with optical rotary encoders.
