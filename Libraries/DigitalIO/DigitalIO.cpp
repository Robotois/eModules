/* 
 * File:   DigitalIO.cpp
 * Author: yova
 * 
 * Created on 21 de mayo de 2016, 01:57 PM
 */

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

#include "DigitalIO.h"

DigitalIO::DigitalIO() {
}

/**
 * Initializes a single IO pin as Input/Output.
 * @param _ioPin
 * @param ioDirection
 */
DigitalIO::DigitalIO(uint8_t _io_pin, uint8_t io_direction) {
    io_pin = _io_pin;
    switch(io_direction){
        case AS_INPUT:
            setAsInput();
            break;
        case AS_OUTPUT:
            setAsOutput();
            break;
        default:
            printf("Error asigning the IO direction of the IO Pin...\n");
            return;
    }
}

//DigitalIO::DigitalIO(uint8_t _io_header,uint8_t io1_dir,uint8_t io2_dir) {
//    switch (_io_header){
//        case DIGITAL_HEADER1:
//            io_pin1 = DIGITAL_HEADER1_1;
//            io_pin2 = DIGITAL_HEADER1_2;.
//            break;
//        case DIGITAL_HEADER2:
//            io_pin1 = DIGITAL_HEADER2_1;
//            io_pin2 = DIGITAL_HEADER2_2;.
//            break;
//        case DIGITAL_HEADER3:
//            io_pin1 = DIGITAL_HEADER3_1;
//            io_pin2 = DIGITAL_HEADER3_2;.
//            break;
//        case DIGITAL_HEADER3:
//            io_pin1 = DIGITAL_HEADER3_1;
//            io_pin2 = DIGITAL_HEADER3_2;.
//            break;
//    }
//                
//    switch(io1_dir){
//        case AS_INPUT:
//            setAsInput(io_pin1);
//            break;
//        case AS_OUTPUT:
//            setAsOutput(io_pin1);
//            break;
//        default:
//            printf("Error asigning the IO direction of the IO Pin...\n");
//            return;
//    }
//    switch(io2_dir){
//        case AS_INPUT:
//            setAsInput(io_pin2);
//            break;
//        case AS_OUTPUT:
//            setAsOutput(io_pin2);
//            break;
//        default:
//            printf("Error asigning the IO direction of the IO Pin...\n");
//            return;
//    }
//}

DigitalIO::DigitalIO(const DigitalIO& orig) {
}

DigitalIO::~DigitalIO() {
}

/**
 * Set the IO pin as output.
 */
void DigitalIO::setAsOutput(){
    bcm2835_gpio_fsel(io_pin, BCM2835_GPIO_FSEL_OUTP);
}

/**
 * Set the IO pin as input, and enables the pull-up resistor.
 */
void DigitalIO::setAsInput(){
    bcm2835_gpio_fsel(io_pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(io_pin, BCM2835_GPIO_PUD_UP);
}

/**
 * Write the given state to the output pin, it is preferred to use the defined 
 * values in the BCM2835 library: HIGH(1), LOW(0).
 * @param state
 */
void DigitalIO::write(uint8_t state){
    bcm2835_gpio_write(io_pin, state);
}

/**
 * Enables the rise event detection for the input pin.
 */
void DigitalIO::riseEventEnable(){
    bcm2835_gpio_aren(io_pin);
}

/**
 * Returns true if the rise event was detected, otherwise it will return 
 * false. It is important to consider that once the event is detected, it is disabled
 * so it won't trigger again and produce undesirable behavior. 
 * @return 
 */
bool DigitalIO::riseEventDetected(){
    if(bcm2835_gpio_eds(io_pin)){
        bcm2835_gpio_set_eds(io_pin);
        bcm2835_gpio_clr_aren(io_pin);
        return true;
    }
    
    return false;
}

/**
 * Enables the fall event detection for the input pin.
 */
void DigitalIO::fallEventEnable(){
    bcm2835_gpio_afen(io_pin);
}

/**
 * Returns true if the fall event was detected, otherwise it will return 
 * false. It is important to consider that once the event is detected, it is disabled
 * so it won't trigger again and produce undesirable behavior. 
 * @return 
 */
bool DigitalIO::fallEventDetected(){
    if(bcm2835_gpio_eds(io_pin)){
        bcm2835_gpio_set_eds(io_pin);
        bcm2835_gpio_clr_afen(io_pin);
        return true;
    }
    
    return false;
}
