/* 
 * File:   LCDModule.cpp
 * Author: yova
 * 
 * Created on 28 de mayo de 2016, 02:38 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <unistd.h>
#include <string>
#include "../../Libraries/Timer/AccurateTiming.h"

#include "LCDModule.h"

LCDModule::LCDModule(uint8_t _addr) {
    mcp = new MCP23008(_addr);
    
  _displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
  
  // the I/O expander pinout
  _rs_pin = 1;
  _rw_pin = 255;
  _enable_pin = 2;
  _backlight_pin = 7;
  
  _data_pins[0] = 3;  // really d4
  _data_pins[1] = 4;  // really d5
  _data_pins[2] = 5;  // really d6
  _data_pins[3] = 6;  // really d7
  _data_pins[4] = _rs_pin; // Reset Pin
  _data_pins[5] = _enable_pin; // Enable Pin
  _data_pins[6] = _backlight_pin;  // BackLight enable pin
  
  initializeLCD();
}

LCDModule::LCDModule(const LCDModule& orig) {
}

LCDModule::~LCDModule() {
    delete mcp;
}

void LCDModule::initializeLCD(){
    // - Set all the putput pins
    mcp->setDir(_data_pins,MCP23008_OUTPUT,7);
    
    // - Enable the Backlight
    mcp->digitalWrite(_backlight_pin,MCP23008_HIGH);
    
//    if(lines > 1){
//        _displayfunction |= LCD_2LINE;
//    }
    
    _numlines = 2;
    _currline = 0;
    
    // - Initialization delay, which is not really necessary since the RPI takes
    // some time to start up, But to keep consistency with the general application
    // case, we will perform initialization as usual.
    usleep(15000);
    // - Setup for begining to send commands
    _write_pins[0] = _rs_pin; _data_write[0] = MCP23008_LOW;
    _write_pins[1] = _enable_pin; _data_write[1] = MCP23008_LOW;
    mcp->writeMultiGPIO(_write_pins,_data_write,2);
    
    // - Put the LCD into 4 bit mode
    writeData(0x03);
    uDelay(4120);
    
    writeData(0x03);
    uDelay(120);

    writeData(0x03);
//    uDelay(150);
    
    writeData(0x02);
//    uDelay(150);

    command(LCD_FUNCTIONSET | _displayfunction);
    
    // turn the display on with no cursor or blinking default    
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
    display();    
    
    clear();
    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    command(LCD_ENTRYMODESET | _displaymode);
}

void LCDModule::writeData(uint8_t value){
    uint8_t io_mask;
    
    // - Read the current GPIO status
    io_mask = mcp->readGPIO();
    
    for(uint8_t i = 0; i < 4; i++){
        if(_data_pins[i] > 7 ){
            printf("Error writing IO output to the Digital IO Device...\n");
            return;
        }
        
        io_mask &= ~(1 << _data_pins[i]); // - Clear current bit
        // Two steps: Obtain the value of the current bit, and set such value to the current bit
        io_mask |= ((value >> i) & 0x01) << _data_pins[i];
    }
    
    // Make sure enable is LOW
    io_mask &= ~(1 << _enable_pin);
    mcp->writeGPIO(io_mask);    
    
    uDelay(1);
    
    io_mask |= (1 << _enable_pin); // Enable to High
    mcp->writeGPIO(io_mask);
    
    uDelay(1);
    
    io_mask &= ~(1 << _enable_pin); // Enable to LOW
    mcp->writeGPIO(io_mask);    
    
    uDelay(1);
}

void LCDModule::send(uint8_t value, uint8_t mode){
    mcp->digitalWrite(_rs_pin,mode);
    
    writeData((uint8_t)(value>>4));
    writeData(value);
}

void LCDModule::command(uint8_t value){
    send(value,MCP23008_LOW);
}

/********** high level commands, for the user! */
void LCDModule::clear(){
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  uDelay(2000);  // this command takes a long time!
}

void LCDModule::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}


void LCDModule::printChar(char _char){
    send(_char,MCP23008_HIGH);
}

uint8_t LCDModule::message(std::string _string){
    uint8_t right_spaces = 0, length = 0;
    for(char& c:_string){
        length++;
        if(c == '\n'){
            nextLine();
            right_spaces = length;
            length = 0;
        }else{
            printChar(c);
        }
    }
    
    if(length > right_spaces){
        right_spaces = length;
    }
    
    if(right_spaces > 40){
       right_spaces =  24;
    }else{
        if(right_spaces >= 16)
            right_spaces -= 16; 
        else
            right_spaces = 0;
    }
    
    return right_spaces;
}

void LCDModule::autoScroll(uint8_t right_spaces){
    uint8_t counter = 0;
    mDelay(500);
    while(1){
        if(counter < right_spaces){
            mDelay(500);
            scrollLeft();
        }else{
            mDelay(500);
            home();
            counter = 0;
        }
        counter++;        
    }
}

void LCDModule::nextLine(){
    command(LCD_SETDDRAMADDR | LCD_NEXTLINE_DDRAMADDR);
}

void LCDModule::scrollRight() {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCDModule::scrollLeft() {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCDModule::home(){
  command(LCD_RETURNHOME);  // set cursor position to zero
  uDelay(2000);  // this command takes a long time!
}