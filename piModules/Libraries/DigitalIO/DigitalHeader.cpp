/* 
 * File:   DigitalHeader.cpp
 * Author: yova
 * 
 * Created on 25 de mayo de 2016, 12:25 PM
 */

#include "DigitalHeader.h"
#include <iostream>
#include <stdlib.h>
#include <bcm2835.h>

DigitalHeader::DigitalHeader() {
}

DigitalHeader::DigitalHeader(uint8_t _io_header,uint8_t io1_dir,uint8_t io2_dir) {
    switch (_io_header){
        case DIGITAL_HEADER1:
            io_pin1 = DIGITAL_HEADER1_1;
            io_pin2 = DIGITAL_HEADER1_2;
            break;
        case DIGITAL_HEADER2:
            io_pin1 = DIGITAL_HEADER2_1;
            io_pin2 = DIGITAL_HEADER2_2;
            break;
        case DIGITAL_HEADER3:
            io_pin1 = DIGITAL_HEADER3_1;
            io_pin2 = DIGITAL_HEADER3_2;
            break;
        case DIGITAL_HEADER4:
            io_pin1 = DIGITAL_HEADER4_1;
            io_pin2 = DIGITAL_HEADER4_2;
            break;
        default:
            printf("Wrong Header selection...\n");
            exit(EXIT_FAILURE);
    }
    
    bcm_init();
    
    switch(io1_dir){
        case AS_INPUT:
            asInput(io_pin1);
            break;
        case AS_OUTPUT:
            asOutput(io_pin1);
            break;
        default:
            printf("Error asigning the IO direction of the IO Pin...\n");
            exit(EXIT_FAILURE);
    }
    switch(io2_dir){
        case AS_INPUT:
            asInput(io_pin2);
            break;
        case AS_OUTPUT:
            asOutput(io_pin2);
            break;
        default:
            printf("Error asigning the IO direction of the IO Pin...\n");
            exit(EXIT_FAILURE);
    }
}

DigitalHeader::DigitalHeader(const DigitalHeader& orig) {
}

DigitalHeader::~DigitalHeader() {
    bcm_end();
}

/**
 * Set the IO pin as output.
 */
void DigitalHeader::asOutput(uint8_t io_pin){
    bcm2835_gpio_fsel(io_pin, BCM2835_GPIO_FSEL_OUTP);
}

/**
 * Set the IO pin as Input.
 */
void DigitalHeader::asInput(uint8_t io_pin){
    bcm2835_gpio_fsel(io_pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(io_pin, BCM2835_GPIO_PUD_UP);
}

/**
 * Write the given state to the output pin, it is preferred to use the defined 
 * values in the BCM2835 library: HIGH(1), LOW(0).
 * @param io_pin
 * @param state
 */
void DigitalHeader::write(uint8_t io_pin,uint8_t state){
    bcm2835_gpio_write(io_pin, state);
}

/**
 * Write the given state to the output pin, it is preferred to use the defined 
 * values in the BCM2835 library: HIGH(1), LOW(0).
 * @param io_pin
 */
uint8_t DigitalHeader::read(uint8_t io_pin){
    return bcm2835_gpio_lev(io_pin);
}

/**
 * Enables the rise event detection for the input pin.
 */
void DigitalHeader::riseEnable(uint8_t io_pin){
    bcm2835_gpio_aren(io_pin);
}

/**
 * Returns TRUE if the rise event was detected in the given IO Pin, otherwise it 
 * will return FALSE. It is important to consider that once the event is detected, 
 * this event is disabled so it won't trigger again and produce undesirable behavior. 
 * @param io_pin
 * @return 
 */
bool DigitalHeader::riseDetected(uint8_t io_pin){
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
void DigitalHeader::fallEnable(uint8_t io_pin){
    bcm2835_gpio_afen(io_pin);
}

/**
 * Returns TRUE if the fall event was detected in the given IO Pin, otherwise it 
 * will return FALSE. It is important to consider that once the event is detected, 
 * this event is disabled so it won't trigger again and produce undesirable behavior. 
 * @param io_pin
 * @return 
 */
bool DigitalHeader::fallDetected(uint8_t io_pin){
    if(bcm2835_gpio_eds(io_pin)){
        bcm2835_gpio_set_eds(io_pin);
        bcm2835_gpio_clr_afen(io_pin);
        return true;
    }
    
    return false;
}

/**
 * It is only initialized the GPIO, in this module we don't use the I2C bus...
 */
void DigitalHeader::bcm_init(){
    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }    
}

void DigitalHeader::bcm_end(){
    bcm2835_close();    
}