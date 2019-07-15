// (C)2019 Pawel A. Hernik

/*
 128x64 ST7920 connections in SPI mode (only 6 wires between LCD and MCU):

 #01 GND  -> GND
 #02 VCC  -> VCC (5V)
 #04 RS   -> D10/CS or any pin
 #05 R/W  -> D11/MOSI
 #06 E    -> D13/SCK
 #15 PSB  -> GND (for SPI mode)
 #19 BLA  -> D9, VCC or any pin via 300ohm resistor
 #20 BLK  -> GND
*/

#define LCD_BACKLIGHT  9
#define LCD_CS         10

#include "ST7920_SPI.h"
#include <SPI.h>
ST7920_SPI lcd(LCD_CS);

// from PropFonts library
#include "c64enh_font.h"
#include "tiny3x7sq_font.h"

char buf[20];

void setup() 
{
  Serial.begin(9600);
  pinMode(LCD_BACKLIGHT, OUTPUT);
  //analogWrite(LCD_BACKLIGHT,30);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  SPI.begin();
  lcd.init();
  lcd.cls();
  for(int j=1;j<17;j++) { lcd.setDither(j); lcd.fillRectD((j-1)*8,0,8,64,1); }
  lcd.display(0); delay(5000);
}

void sample(int s)
{
  lcd.cls();
  lcd.setDither(s);
  lcd.setFont(c64enh);
  snprintf(buf,20,"Pattern: %02d",s);
  lcd.printStr(ALIGN_CENTER, 2, buf);
  lcd.fillRectD(4,13,68,32,1);
  lcd.fillCircleD(100,28,16,1);
  for(int j=1;j<17;j++) {
    lcd.setFont(Tiny3x7SqPL);
    snprintf(buf,20,"%2d",j);
    lcd.printStr((j-1)*8, 64-8*2, buf);
    lcd.setDither(j);
    lcd.fillRectD((j-1)*8,64-8,8,8,1);
  }
  lcd.display(0);
  delay(500);
}

void loop() 
{

/*
  lcd.cls();
  for(int j=1;j<17;j++) {
    lcd.setDither(j);
    lcd.fillRectD((j-1)*4,0,4,j*4,1);
  //lcd.display(0); delay(1000);
  }
  for(int j=15;j>=0;j--) {
    lcd.setDither(j);
    lcd.fillRectD((15-j)*4+63,0,4,j*4,1);
  lcd.display(0); delay(1000);
  }
  lcd.display(0);
  delay(5000);*/
  for(int i=0;i<=16;i++) sample(i);
  for(int i=16;i>0;i--) sample(i);
}

