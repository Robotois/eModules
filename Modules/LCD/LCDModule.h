/* 
 * File:   LCDModule.h
 * Author: yova
 *
 * Created on 28 de mayo de 2016, 02:38 PM
 */

#ifndef LCDMODULE_H
#define	LCDMODULE_H

#include "../../Libraries/MCP23008/MCP23008.h"
#include <string>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define LCD_NEXTLINE_DDRAMADDR 0x40

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

#define LCD_ADDRESS 0x04 // - Default Address


class LCDModule {
public:
    LCDModule(uint8_t _addr = 0x00);
    LCDModule(const LCDModule& orig);
    virtual ~LCDModule();
    
    void initializeLCD();
    void printChar(char _char);
    void message(std::string _string);
    void scrollRight();
    void scrollLeft();
    void autoScroll(uint8_t right_spaces);
    void setBacklight(uint8_t status);
    void bklBlink();
    void noDisplay();
    void setCursor(uint8_t row, uint8_t col);
    void clear();
    void home();
    
    void release();
    
private:
    uint8_t _rs_pin; // LOW: command.  HIGH: character.
    uint8_t _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
    uint8_t _enable_pin; // activated by a HIGH pulse.
    uint8_t _backlight_pin; // activated by a HIGH pulse.
    uint8_t _data_pins[8],_write_pins[8], _data_write[8];

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;

    uint8_t _initialized;

    uint8_t _numlines,_currline;

//    uint8_t _SPIclock, _SPIdata, _SPIlatch;
//    uint8_t _SPIbuff;

    uint8_t _i2cAddr;

    MCP23008 *mcp;
    
    void writeData(uint8_t value);
    void send(uint8_t value, uint8_t mode);
    void command(uint8_t value);
    
    void display();
    void nextLine();    

};

#endif	/* LCDMODULE_H */

