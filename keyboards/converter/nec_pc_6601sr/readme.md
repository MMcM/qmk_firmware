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

## Matrix

Most of these are based on the base character, with others chosen to make the matrix smaller and the mapping reasonably compact.

```
+---+  +---+
|03 |  |08 |
+---+  +---+

+---+---+-------+-------+-------+-------+-------+---+---+-----+
|8A*|8D |80     |81     |82     |83     |84     |0C |7E |7F   |
+-------------------------------------------------------------+
|1B |31 |32 |33 |34 |35 |36 |37 |38 |39 |30 |2D |5E |5C |12   |
+-------------------------------------------------------------+
|09   |71 |77 |65 |72 |74 |79 |75 |69 |6F |70 |40 |5B |5D |   |
+---------------------------------------------------------|   |
|01    |61 |73 |64 |66 |67 |68 |6A |6B |6C |3B |3A |5F |0D    |
+-------------------------------------------------------------+
|00*     |7A |78 |63 |76 |62 |6E |6D |2C |2E |2F |00* |1E*|8E |
+-------------------------------------------------------------+
|8B |02 |20*                                      |1D*|1F*|1C*|
+---+---+-----------------------------------------+---+---+---+
```

The seven game keys are marked with `*`.
