# NEC PC-6601SR "Mr. PC"

A converter for the NEC PC-6601SR keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 6601SR, A-Star Micro  

Make example for this keyboard (after setting up your build environment):

    make converter/nec_pc_6601sr:default

## Protocol

The keyboard interfaces either using infrared or a coiled cable.

The protocol uses pulse distance encoding in either case. Although the timing is different between them, the bit encoding is the same.

Details of the protocol came be found [here](http://sbeach.seesaa.net/article/408962018.html) and [here](http://sbeach.seesaa.net/article/408970013.html).

Seven of the keys report that are used for gaming, STOP, SPACE, SHIFT, and the four arrow keys, send key up events. The rest do not.

## Connections

The IR encoding has a 38kHz carrier and reasonably long pulses, do any standard sensor, such as a (TSOP38238)[https://www.adafruit.com/product/157] should work. Its output should connect to PD2.

The wired connection is an RJ 4P4C jack. The supplied cable is crossover. The pin numbers below are for the converter (PC) end.

The keyboard is always powered by batteries. The PC passes 5V only to pull up a sense line and indicate that the cable is plugged in, causing the keyboard to switch from IR to wired.

| RJ | Keyboard | PC        | AVR |
|----|----------|-----------|-----|
|  1 | sense PC | high      | +5V |
|  2 | ground   | sense kbd | PD1 |
|  3 | data     | data      | PD0 |
|  4 | ground   | ground    | GND |
