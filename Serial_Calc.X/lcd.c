#include "main.h"

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Send(unsigned char byt) {
    //if (RS_PIN == 1)

        E_PIN = 0;
    __delay_us(30);

    unsigned char D4, D5, D6, D7;

    D4 = (unsigned char)(byt & 0b00010000);
    D5 = (unsigned char)(byt & 0b00100000);
    D6 = (unsigned char)(byt & 0b01000000);
    D7 = (unsigned char)(byt & 0b10000000);

    if (D4)
        DB4_PIN = 1;
    else
        DB4_PIN = 0;

    if (D5)
        DB5_PIN = 1;
    else
        DB5_PIN = 0;

    if (D6)
        DB6_PIN = 1;
    else
        DB6_PIN = 0;

    if (D7)
        DB7_PIN = 1;
    else
        DB7_PIN = 0;

    E_PIN = 1;
    __delay_ms(4);
    E_PIN = 0;

    D4 = (unsigned char)(byt & 0b00000001);
    D5 = (unsigned char)(byt & 0b00000010);
    D6 = (unsigned char)(byt & 0b00000100);
    D7 = (unsigned char)(byt & 0b00001000);

    if (D4)
        DB4_PIN = 1;
    else
        DB4_PIN = 0;

    if (D5)
        DB5_PIN = 1;
    else
        DB5_PIN = 0;

    if (D6)
        DB6_PIN = 1;
    else
        DB6_PIN = 0;

    if (D7)
        DB7_PIN = 1;
    else
        DB7_PIN = 0;


    E_PIN = 1;
    __delay_ms(4);
    E_PIN = 0;
}

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Send_Com(unsigned char byte) {
    RS_PIN = 0;
    __delay_us(30); //2

    Lcd_Send(byte);

}

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Send_Char(unsigned char byte) {
    RS_PIN = 1;
    __delay_us(30); //2

    Lcd_Send(byte);

}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Init(void) {
    E_PIN = 1;
    __delay_ms(20); //15

    RS_PIN = 0;
    __delay_ms(20); //15

    Lcd_Send(0x03);
    __delay_ms(5);
    Lcd_Send(0x03);
    __delay_ms(16);
    Lcd_Send(0x03);
    __delay_ms(10);
    Lcd_Send(0x02);
    __delay_ms(10);
    Lcd_Send(0x28);
    __delay_ms(15); //10

    Lcd_Send(0x06);
    __delay_ms(15); //10
    
    Lcd_Send(0x08);
    __delay_ms(15); //10
    
    RS_PIN = 1;
    __delay_ms(15); //10
    //Set_Turkce();

}




void lcd_kinit(void)
{
    E_PIN = 1;
    __delay_ms(15);
    
RS_PIN = 0;

                Lcd_Send(0x33);
                __delay_ms(10);
                Lcd_Send(0x33);
                __delay_ms(10);
                Lcd_Send(0x33);
                __delay_ms(10);
                Lcd_Send(0x20);
                __delay_ms(10);
                Lcd_Send(0x20);
                __delay_ms(10);
                Lcd_Send(0x28);
                __delay_ms(10);
                Lcd_Send(0x08);
                __delay_ms(10);
                Lcd_Send(0x0e);
                __delay_ms(10);
                Lcd_Send(0x01);
                __delay_ms(10);
RS_PIN = 1;

}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Cls(void) {
    RS_PIN = 0;
    __delay_us(30); //2

    Lcd_Send(0x01);
    __delay_ms(15); //10
    Lcd_Send(0x02);
    __delay_ms(15); //10
    Lcd_Send(0x0C);
    __delay_ms(15); //10

    RS_PIN = 1;

    __delay_ms(50);
}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Print(const char *q) {
    RS_PIN = 1;
    __delay_us(30); //2

    while (*q) {

        Lcd_Send(*q++);
        __delay_us(30); //2

    }
    Cursor_Hide();
}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Cursor_Blink(void) {
    RS_PIN = 0;
    __delay_us(30); //2

    Lcd_Send(0x0F);
    __delay_ms(5);
}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Cursor_Hide(void) {
    RS_PIN = 0;
    __delay_us(30); //2

    Lcd_Send(0x0C);
    __delay_ms(5);
}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Val(unsigned int wrd) {

    unsigned char num100, num10, num1;

    RS_PIN = 1;
    __delay_us(30);

    num100 = (wrd / 100) + 48;
    num10 = (wrd % 100) / 10 + 48;
    num1 = (wrd % 10) + 48;

    if (num100 != 0x30) {
        Lcd_Send(num100);
        __delay_us(30);
        Lcd_Send(num10);
        __delay_us(30);
        Lcd_Send(num1);
        __delay_us(30);
    } else if (num10 != 0x30) {
        Lcd_Send(num10);
        __delay_us(30);
        Lcd_Send(num1);
        __delay_us(30);
    } else {
        Lcd_Send(num1);
        __delay_us(30);

    }

}


//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Num2(unsigned char byt) {
    unsigned char num10, num1;

    RS_PIN = 1;
    __delay_us(30);

    num10 = (unsigned char)((byt / 10) + 48);
    num1 = (unsigned char)((byt % 10) + 48);

    if (num10 != 0x30)
        Lcd_Send(num10);
    __delay_us(30);
    Lcd_Send(num1);
    __delay_us(30);
}

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Num3(unsigned int wrd) {
    unsigned char num100, num10, num1;

    RS_PIN = 1;
    __delay_us(30);

    num100 = (wrd / 100) + 48;
    num10 = (wrd % 100) / 10 + 48;
    num1 = (wrd % 10) + 48;

    if (num100 != 0x30) {
        Lcd_Send(num100);
        __delay_us(30);
        Lcd_Send(num10);
        __delay_us(30);
        Lcd_Send(num1);
        __delay_us(30);
    } else if (num10 != 0x30) {
        Lcd_Send(num10);
        __delay_us(30);
        Lcd_Send(num1);
        __delay_us(30);
    } else {
        Lcd_Send(num1);
        __delay_us(30);

    }

}

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_Goto(unsigned char line, unsigned char satir) {
    RS_PIN = 0;
    __delay_us(30); //2

    Lcd_Send((unsigned char)(line + --satir));
    //__delay_ms(5);
}

void Lcd_PrintX(unsigned char line, unsigned char satir, unsigned char cursor, unsigned char len, unsigned char *p)
{
    Lcd_Send_Com((unsigned char)(line + --satir));
    __delay_ms(5);

    RS_PIN = 1;
    __delay_us(30); //2

    unsigned char i;
    for(i=0; i<len; i++){
		Lcd_Send(*p++);
        __delay_us(30); //2
	}

    //goto line-satir - cursor blink
    RS_PIN = 0;
    __delay_us(30); //2
    Lcd_Send_Com((unsigned char)(line + --cursor));
    __delay_ms(5);
    
    //Cursor_Blink
    Lcd_Send(0x0F);
    __delay_ms(5);
}

//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_PrintLine(unsigned char line, unsigned char satir, unsigned char *p) {

    Lcd_Send_Com((unsigned char)(line + --satir));
    __delay_ms(5);

    RS_PIN = 1;
    __delay_us(30); //2

    while (*p != 0) {
        Lcd_Send(*p++);
        __delay_us(30); //2
    }
}
//----------------------------------------//
//                                        //
//----------------------------------------//
void Lcd_PrintLineC(unsigned char line, unsigned char satir, const unsigned char *p) {

    Lcd_Send_Com((unsigned char)(line + --satir));
    __delay_ms(5);

    RS_PIN = 1;
    __delay_us(30); //2

    while (*p != 0) {
        Lcd_Send(*p++);
        __delay_us(30); //2
    }
}


//----------------------------------------//
//                                        //
//----------------------------------------//
void LcdcreateChar(unsigned char location, const unsigned char* map) {
    RS_PIN = 1;
	//location &= 0x7;   //0-7
	Lcd_Send_Com(0x40 | (location << 3));
	for (unsigned char i=0; i<8; i++) {
		Lcd_Send_Char(map[i]);
	}
}


/*
void begin(void) {

	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (_rows > 1) {
		_displayfunction |= LCD_2LINE;
	}

	// for some 1 line displays you can select a 10 pixel high font
	if ((_charsize != 0) && (_rows == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	__delay_ms(50);

	// Now we pull both RS and R/W low to begin commands

	__delay_ms(1000);

	// we start in 8bit mode, try to set 4 bit mode
	Lcd_Send_Com(0x03 << 4);
	__delay_us(4500); // wait min 4.1ms

	// second try
	write4bits(0x03 << 4);
	__delay_us(4500); // wait min 4.1ms

	// third go!
	write4bits(0x03 << 4);
	__delay_us(150);

	// finally, set to 4-bit interface
	write4bits(0x02 << 4);

	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	// clear it off
	clear();

	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);

	home();
}


void LiquidCrystal_I2C::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	__delay_us(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	__delay_us(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > _rows) {
		row = _rows-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C::noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C::noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_I2C::noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C::scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_I2C::scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C::leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C::rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C::autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C::noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_I2C::createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void LiquidCrystal_I2C::noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void LiquidCrystal_I2C::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}
bool LiquidCrystal_I2C::getBacklight() {
  return _backlightval == LCD_BACKLIGHT;
}




inline void LiquidCrystal_I2C::command(uint8_t value) {
	send(value, 0);
}

inline size_t LiquidCrystal_I2C::write(uint8_t value) {
	send(value, Rs);
	return 1;
}




// write either command or data
void LiquidCrystal_I2C::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	write4bits((highnib)|mode);
	write4bits((lownib)|mode);
}

void LiquidCrystal_I2C::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void LiquidCrystal_I2C::expanderWrite(uint8_t _data){
	Wire.beginTransmission(_addr);
	Wire.write((int)(_data) | _backlightval);
	Wire.endTransmission();
}

void LiquidCrystal_I2C::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	__delay_us(1);		// enable pulse must be >450ns

	expanderWrite(_data & ~En);	// En low
	__delay_us(50);		// commands need > 37us to settle
}

void LiquidCrystal_I2C::load_custom_character(uint8_t char_num, uint8_t *rows){
	createChar(char_num, rows);
}

void LiquidCrystal_I2C::setBacklight(uint8_t new_val){
	if (new_val) {
		backlight();		// turn backlight on
	} else {
		noBacklight();		// turn backlight off
	}
}

void LiquidCrystal_I2C::printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed
	print(c);
}
*/