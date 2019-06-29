// (C)2019 Pawel A. Hernik

/*
 128x64 ST7920 connections in SPI mode (only 6 wires between LCD and MCU):

 #01 GND  -> GND
 #02 VCC  -> VCC (5V)
 #04 RS   -> SCK/D13
 #05 R/W  -> MOSI/D11
 #06 E    -> CS/D10 or any pin
 #15 PSB  -> GND (for SPI mode)
 #19 BLA  -> VCC or any pin via 300ohm
 #20 BLK  -> GND
*/

#define LCD_BACKLIGHT  9
#define LCD_CS         10

#include "ST7920_SPI.h"
#include <SPI.h>
ST7920_SPI lcd(LCD_CS);

// from PropFonts library
#include "c64enh_font.h"

void setup() 
{
  Serial.begin(9600);
  pinMode(LCD_BACKLIGHT, OUTPUT);
  //analogWrite(LCD_BACKLIGHT,30);
  digitalWrite(LCD_BACKLIGHT, HIGH);

  SPI.begin();
  lcd.init();
  lcd.cls();
  lcd.setFont(c64enh);
  lcd.printStr(ALIGN_CENTER, 8, "Buffer #0");
  lcd.fillRect(18,24,32,32,1);
  lcd.fillRect(128-18-32,24,32,32,1);
  lcd.display(0);
  lcd.cls();
  lcd.setFont(c64enh);
  lcd.printStr(ALIGN_CENTER, 64-16, "Buffer #1");
  lcd.fillCircle(64,24,20,1);
  lcd.display(1);
}

void loop() 
{
  lcd.switchBuf(0);
  delay(1000);
  lcd.switchBuf(1);
  delay(1000);
}

