# VT100

A converter for the VT100 terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: VT100, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/vt100:default

# Protocol

The cable from the keyboard that plugs into the terminal has a 1/4" 3-conductor audio plug. Sleeve is ground, tip is +12V DC, and ring is a bi-directional serial signal.

The [VT100 Technical Manual](http://www.bitsavers.org/pdf/dec/terminal/vt100/EK-VT100-TM-003_VT100_Technical_Manual_Jul82.pdf) gives complete details on the encoding. Each end effectively subtracts its own serial output from the combined signal to get the other end's. Each has a CMOS UART. The transmit clock from the terminal to the keyboard comes from an address line in the video processor with an average period of 7.945µs, which works out to 7867 baud. The keyboard does not have its own clock. Instead, the terminal PWM encodes its signals using its clock and one that's about twice as fast: 75% duty-cycle for mark and 25% duty-cycle for space. Using just the edges, the single clock can be reconstituted. And the values average out for the UART.

# Hardware

The [VT100 Schematics](http://www.bitsavers.org/pdf/dec/terminal/vt100/MP00633_VT100_Schematic_Feb82.pdf) give the exact circuits used. The terminal side is Basic Video 6/6, page 19/64 and the keyboard side Full Keyboard 1/3, page 34/64. The parts that compose and decompose the bi-directional signal are borrowed more or less directly.

An [earlier effort](https://loomcom.com/blog/0065_retrochallenge_2013.html), publicized on [Hackaday](https://hackaday.com/2013/08/13/usb-adapter-for-an-old-vt100-keyboard/), also did just that. It went all the way, though, including a CMOS UART and an external crystal, instead of using the Teensy. That crystal is 1MHz, divided by a counter, so the clock period is 8µs, or 7812.5 baud.

UARTs at this relatively slow speed are pretty forgiving. And the keyboard does not have its own clock. So, if the UART is set for 7812.5 baud and PWM generated at a matching frequency, things should work. To do this, two of the Atmel's timers are set to generate square waves of 4µs and 8µs and NANDed combined just in like the originals.

Relative to the [earlier schematic](https://github.com/sethm/vt100_usb/blob/master/schematic.png), the changes are:

* Leave out the crystal, UART, and dividing counter.
* Use `TX` (`D3`) for `SER_OUT` and `RX` (`D2`) for `SER_IN`.
* Use `B5` for `CLK_B` and `C6` for `CLK_C`. Phase can be set in software, so no inverter is needed.
