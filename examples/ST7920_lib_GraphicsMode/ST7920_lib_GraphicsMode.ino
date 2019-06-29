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

void setup() 
{
  Serial.begin(9600);
  pinMode(LCD_BACKLIGHT, OUTPUT);
  //analogWrite(LCD_BACKLIGHT,30);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  SPI.begin();
  lcd.init();
  lcd.cls();
  lcd.drawRectD(0,0,128,64,1);

  lcd.drawRect(9,5,30,20,1);
  lcd.fillRect(9+40,5,30,20,2);
  lcd.fillRectD(9+80,5,30,20,1);
  //lcd.drawRect(9+80,5,30,20,1);

  lcd.drawCircle(9+15,44,15,1);
  lcd.fillCircle(9+40+15,44,15,1);
  lcd.fillCircleD(9+80+15,44,15,1);
  //lcd.drawCircle(9+80+15,44,15+1,1);

  lcd.display(0);
}

void loop() 
{
}

