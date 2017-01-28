/* 
 * File:   LED.cpp
 * Author: yova
 * 
 * Created on 8 de septiembre de 2016, 05:48 PM
 */

#include <cstdio>

#include "LED.h"

LED::LED(uint8_t _header) {
    IOHeader = new DigitalHeader(_header,(uint8_t)AS_OUTPUT,(uint8_t)AS_OUTPUT);
}

LED::LED(const LED& orig) {
}

LED::~LED() {
}


void LED::write(uint8_t state){
    IOHeader->io1_write(state);
}

void LED::release(){
    printf("[LEDModule] => Released\n");
    IOHeader->release();
    delete IOHeader;    
}