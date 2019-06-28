// (C)2019 Pawel A. Hernik

/*
 128x64 ST7920 connections (SPI)

 #01 GND  -> GND
 #02 VCC  -> VCC (5V)
 #04 RS   -> SCK/D13
 #05 R/W  -> MOSI/D11
 #06 E    -> CS/D10 or any pin
 #15 PSB  -> GND (for SPI mode)
 #19 BLA  -> VCC od any pin via 300ohm?
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
  lcd.setGfxMode(false);

  // Watch https://www.youtube.com/watch?v=OyUXVsbAcmo for built-in font codes
  uint16_t star1[] = { 0xa1ee, 0 };
  uint16_t star2[] = { 0xa1ef, 0 };
  //uint16_t signs[] = { 0xa170,0xa171,0xa173,0xa174,0xa175,0xa176,0 };
  uint16_t signs1[] = { 0xa170,0xa171,0 };
  uint16_t signs2[] = { 0xa173,0xa174,0 };
  //uint16_t roman[] = { 0xa271,0xa271+11,0 };
  uint16_t fnt16x16[] = { 0xa300+'F', 0xa300+'n',0xa300+'t',0xa331,0xa336, 0xa141,0xa331,0xa336,0 };
  uint16_t date[] = { 0xa161, 0xa300+'1', 0xa300+'5', 0xa270+8, 0xa300+'1', 0xa300+'4', 0xa300+'1', 0xa300+'0',0 };
  uint16_t temp[] = { 0xa300+'+', 0xa300+'2', 0xa300+'7', 0xa166,0 };

  lcd.printTxt(LCD_LINE0+0,star1);
  lcd.printTxt(LCD_LINE0+7,star2);
  lcd.printTxt(LCD_LINE0+2,"Font16x8");
  //lcd.printTxt(LCD_LINE1+2,"Line #1");
  lcd.printTxt(LCD_LINE1,fnt16x16);
  lcd.printTxt(LCD_LINE2+2,temp);
  lcd.printTxt(LCD_LINE2+0,signs1);
  lcd.printTxt(LCD_LINE2+6,signs2);
  //lcd.printTxt(LCD_LINE2+4,roman);
  lcd.printTxt(LCD_LINE3,date);
}

void loop() 
{
}

