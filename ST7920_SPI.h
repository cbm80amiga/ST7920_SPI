// ST7920 128x64 LCD driver
// 2019 by Pawel A. Hernik

/*
 128x64 ST7920 connections (SPI)

 #01 GND  -> GND
 #02 VCC  -> VCC (5V)
 #04 RS   -> SCK/D13
 #05 R/W  -> MOSI/D11
 #06 E    -> CS/D10 or any pin
 #15 PSB  -> GND (for SPI mode)
 #19 BLA  -> VCC via 300ohm
 #20 BLK  -> GND

*/

#ifndef _ST7920_SPI_H
#define _ST7920_SPI_H 

#include <Arduino.h>
#include <avr/pgmspace.h>

// ST7920 Commands

#define LCD_CLS         0x01
#define LCD_HOME        0x02
#define LCD_ADDRINC     0x06
#define LCD_DISPLAYON   0x0C
#define LCD_DISPLAYOFF  0x08
#define LCD_CURSORON    0x0E
#define LCD_CURSORBLINK 0x0F
#define LCD_BASIC       0x30
#define LCD_EXTEND      0x34
#define LCD_GFXMODE     0x36
#define LCD_TXTMODE     0x34
#define LCD_STANDBY     0x01
#define LCD_SCROLL      0x03
#define LCD_SCROLLADDR  0x40
#define LCD_ADDR        0x80
#define LCD_LINE0       0x80
#define LCD_LINE1       0x90
#define LCD_LINE2       0x88
#define LCD_LINE3       0x98

#define SPI_SPEED (1000000UL)

#ifndef SCR_WD
#define SCR_WD  128
#define SCR_HT  64
#endif

#define ALIGN_LEFT    0
#define ALIGN_RIGHT  -1 
#define ALIGN_CENTER -2

struct _propFont
{
  const uint8_t* font;
  int8_t xSize;
  uint8_t ySize;
  uint8_t firstCh;
  uint8_t lastCh;
  uint8_t minCharWd;
  uint8_t minDigitWd;
};

// ---------------------------------
class ST7920_SPI {
public:
	ST7920_SPI(byte cs);

  void init();
  void sendCmd(byte b);
  void sendData(byte b);
  void switchBuf(byte b);
  void display(int buf=0);
  void copy(uint8_t x16, uint8_t y, uint8_t w16, uint8_t h, uint8_t buf=0);
  void gotoXY(byte x, byte y);
  void sleep(bool mode=true);
  void setGfxMode(bool mode=true);
  void printTxt(uint8_t pos, char *str);
  void printTxt(uint8_t pos, uint16_t *signs);

  void cls();
  void drawPixel(uint8_t x, uint8_t y, uint8_t col);
  void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t col);
  void drawLineH(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
  void drawLineV(uint8_t x,  uint8_t y0, uint8_t y1, uint8_t col);
  void drawLineVfast(uint8_t x, uint8_t y0, uint8_t y1, uint8_t col);
  void drawLineVfastD(uint8_t x, uint8_t y0, uint8_t y1, uint8_t col);
  void drawLineHfast(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
  void drawLineHfastD(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
  void drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t col);
  void drawRectD(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
  void fillRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t col);
  void fillRectD(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t col);
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t col);
  void fillCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t col);
  void fillCircleD(uint8_t x0, uint8_t y0, uint8_t r, uint8_t col);
  void setDither(uint8_t s);
  int drawBitmap(const uint8_t *bmp, int x, uint8_t y, uint8_t w, uint8_t h);
  int drawBitmap(const uint8_t *bmp, int x, uint8_t y);

  void setFont(const uint8_t* f);
  void setCR(uint8_t _cr) { cr = _cr; }
  void setInvert(uint8_t _inv) { invertCh = _inv; }
  void setFontMinWd(uint8_t wd) { cfont.minCharWd = wd; }
  void setCharMinWd(uint8_t wd) { cfont.minCharWd = wd; }
  void setDigitMinWd(uint8_t wd) { cfont.minDigitWd = wd; }
  int printChar(int xpos, int ypos, unsigned char c);
  int printStr(int xpos, int ypos, char *str);
  int charWidth(uint8_t _ch, bool last=true);
  int strWidth(char *txt);
  unsigned char convertPolish(unsigned char _c);
  static bool isNumber(uint8_t ch);
  static bool isNumberExt(uint8_t ch);
  void setIsNumberFun(bool (*fun)(uint8_t)) { isNumberFun=fun; }
  
public:
  byte scr[SCR_WD*SCR_HT/8];
  byte scrWd = 128/8;
  byte scrHt = 64;
  uint8_t csPin  = 10;

  static byte xstab[8];
  static byte xetab[8];
  static byte pattern[4];
  static const byte ditherTab[4*17];
   
//private:
  bool (*isNumberFun)(uint8_t ch);
  _propFont  cfont;
  /*
  uint8_t xSize;
  uint8_t ySize;
  uint8_t ySize8;
  uint8_t firstCh;
  uint8_t lastCh;
  uint8_t minCharWd;
  uint8_t minDigitWd;
  */
  uint8_t cr;  // carriage return mode for printStr
  uint8_t dualChar;
  uint8_t invertCh;
  uint8_t spacing = 1;	
};
#endif

