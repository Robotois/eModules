/* 
 * File:   Button.cpp
 * Author: yova
 * 
 * Created on 8 de septiembre de 2016, 06:04 PM
 */

#include <stdint.h>

#include "Button.h"

Button::Button(uint8_t header) {
    IOHeader = new DigitalHeader(header,(uint8_t)AS_INPUT,(uint8_t)AS_INPUT);
}

Button::Button(const Button& orig) {
}

Button::~Button() {
    delete IOHeader;
}

uint8_t Button::read(){
    state = IOHeader->read(IOHeader->io_pin1);
    // - Using pull-up resistors, it would return the inverted value.
    return (state ^ (uint8_t)0x01);
}

