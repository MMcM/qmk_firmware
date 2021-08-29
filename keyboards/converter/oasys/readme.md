# Fujitsu OASYS and FM Towns

A converter for the Fujitsu keyboards for OASYS and FM Towns. These have Fujitsu leaf spring switches.
Most of these keyboards have thumb-shift and regular JIS variants.

Additional sources of information:
* https://tepatti.com/blog/005/index.html
* http://m0115.web.fc2.com/main.html
* https://ixsvr.dyndns.org/usb2fmr
* https://kiyoto-y.github.io/

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: FACOM6140KA1, FMT-KB105, Adafruit Itsy-bitsy 5V  

Make example for this keyboard (after setting up your build environment):

    make converter/oasys:default

## Protocol

The keyboard protocol is 9600 baud TTL serial, open-collector, idle hi-Z.

Each report consists of two bytes, the first of which has the high bit set and the second of which has it clear.
In general, the first byte indicates make vs. break, plus whether the keyboard is thumb-shift or JIS, and the second byte is the scan code. There is a special break code for all keys up.
The arrow keys have a rather more complicated protocol, which allows for diagonal motion.

## Connections

The keyboard has a somewhat unusual [HR12](https://www.hirose.com/product/document?clcode=&productname=&series=HR12&documenttype=Catalog&lang=en&documentid=D49402_en) 8-pin connector.

Only three signals are needed, but power is duplicated on two pins each.

| HR12 | Signal        |
|------|---------------|
| 1,2  | GND           |
| 7,8  | +5V           |
| 3    | RX (from kbd) |
