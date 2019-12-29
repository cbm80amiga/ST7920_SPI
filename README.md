# ST7920_SPI
ST7920 SPI 128x64 LCD library with frame buffer

YouTube video:
https://youtu.be/JAJcGKE-0k0

## Features

- ST7920 text mode with built-in CGROM fonts (8x16 and 16x16)
- graphics mode with 128x64 pixels frame buffer
- proportional fonts in graphics mode
- hardware doublebuffer
- simple primitives
  - pixels
  - lines
  - rectangles
  - filled rectangles
  - circles
  - filled circles
- fast ordered dithering (17 patterns)
- ultra fast horizontal and vertical line drawing
- bitmaps drawing
- example programs

## Connections:

|LCD pin|LCD pin name|Arduino|
|--|--|--|
 |#01| GND| GND|
 |#02| VCC |VCC (5V)|
 |#04| RS |  D10/CS or any pin|
 |#05| R/W|  D11/MOSI|
 |#06| E  |  D13/SCK|
 |#15| PSB|  GND (for SPI mode)|
 |#19| BLA | D9, VCC or any pin via 300ohm resistor|
 |#20| BLK | GND|

If you find it useful and want to buy me a coffee or a beer:

https://www.paypal.me/cbm80amiga
