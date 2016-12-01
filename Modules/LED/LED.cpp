/* 
 * File:   LED.cpp
 * Author: yova
 * 
 * Created on 8 de septiembre de 2016, 05:48 PM
 */

#include "LED.h"

LED::LED(uint8_t _header) {
    IOHeader = new DigitalHeader(_header,(uint8_t)AS_OUTPUT,(uint8_t)AS_OUTPUT);
    IOHeader->write(IOHeader->io_pin1,0);
    
}

LED::LED(const LED& orig) {
}

LED::~LED() {
    delete IOHeader;
}


void LED::write(uint8_t state){
    IOHeader->write(IOHeader->io_pin1,state);
}
