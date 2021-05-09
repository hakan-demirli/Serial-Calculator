#ifndef LCD_H
#define	LCD_H

//#include "xc.h"

#define LINE1   0x80
#define LINE2   0xC0
#define LINE3   0x94
#define LINE4   0xD4

#define CHR_UCGEN         0x01
#define CHR_KUMSAATI      0x02
#define CHR_DERECE        0x03
#define CHR_USER          0x04
#define CHR_TEMPEDIT      0x05
#define CHR_TERSBUYUK_A   0x06
#define CHR_KUCUK_A       0x06
#define CHR_TERSKUCUK_A   0x06
#define CHR_PRINTER       0x07

void lcd_kinit(void);
void Lcd_PrintX(unsigned char line, unsigned char satir, unsigned char cursor, unsigned char len, unsigned char *p);
void LcdcreateChar(unsigned char location, const unsigned char* map);
void Lcd_Print(const char *q);
void Lcd_Init(void);
void Lcd_Cls(void);
void Lcd_Send(unsigned char byt);
void Cursor_Blink(void);
void Cursor_Hide(void);

void Lcd_PrintLine(unsigned char line, unsigned char satir, unsigned char *p);
void Lcd_PrintLineC(unsigned char line, unsigned char satir, const unsigned char *p);
void Lcd_Goto(unsigned char line, unsigned char satir);
void lcd_Num3(unsigned int wrd);
void Lcd_Num2(unsigned char byt);
void Lcd_Val(unsigned int wrd);
void Lcd_Send_Char(unsigned char byte);

const unsigned char TempEditSym[] = {
  0x04,
  0x0A,
  0x0A,
  0x0E,
  0x1F,
  0x1F,
  0x0E,
  0x00
};

const unsigned char KumSaatiSym[] = {
  0x1F,
  0x11,
  0x0A,
  0x04,
  0x0A,
  0x1F,
  0x1F,
  0x00
};

const unsigned char UcgenSym[] = {
  0x00,
  0x00,
  0x01,
  0x03,
  0x07,
  0x0F,
  0x1F,
  0x00
};

const unsigned char PrinterSym[] = {
  0x0E,
  0x0A,
  0x0E,
  0x0A,
  0x1F,
  0x11,
  0x1F,
  0x00
};

const unsigned char TersKucukASym[] = {
  0x00,
  0x00,
  0x12,
  0x12,
  0x1E,
  0x12,
  0x0C,
  0x00
};

const unsigned char TersBuyukASym[] = {
  0x11,
  0x11,
  0x11,
  0x1F,
  0x11,
  0x11,
  0x0E,
  0x00
};

const unsigned char KucukASym[] = {
  0x00,
  0x00,
  0x0C,
  0x12,
  0x1E,
  0x12,
  0x12,
  0x00
};

const unsigned char UserSym[] = {
  0x0E,
  0x0E,
  0x04,
  0x1F,
  0x04,
  0x0A,
  0x11,
  0x00
};

const unsigned char DereceSym[] = {
  0x07,
  0x05,
  0x07,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

//----

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

#endif	/* LCD_H */

