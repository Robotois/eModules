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

DigitalHeader::DigitalHeader(uint8_t _io_header,uint8_t _io1_dir,uint8_t _io2_dir) {
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
        case DIGITAL_HEADER5:
            io_pin1 = DIGITAL_HEADER5_1;
            io_pin2 = DIGITAL_HEADER5_2;
            break;
        case DIGITAL_HEADER6:
            io_pin1 = DIGITAL_HEADER6_1;
            io_pin2 = DIGITAL_HEADER6_2;
            break;
        default:
            printf("Wrong Header selection...\n");
            return;
    }
    
    bcm_init();
    io1_dir = _io1_dir;
    io2_dir = _io2_dir;
    switch(io1_dir){
        case AS_INPUT:
            asInput(io_pin1);
            break;
        case AS_OUTPUT:
            asOutput(io_pin1);
            break;
        default:
            printf("Error asigning the IO direction of the IO Pin...\n");
            return;
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
            return;
    }
}

DigitalHeader::DigitalHeader(const DigitalHeader& orig) {
}

DigitalHeader::~DigitalHeader() {
}

/**
 * High level functions, they are intended for an intuitive interaction with the IO
 * pins
 */

void DigitalHeader::io1_asInput(){
    asInput(io_pin1);
}

void DigitalHeader::io1_asOutput(){
    asOutput(io_pin1);
}

void DigitalHeader::io1_write(uint8_t state){
    write(io_pin1,state);
}

uint8_t DigitalHeader::io1_read(){
    return read(io_pin1);
}

void DigitalHeader::io1_riseEnable(){
    riseEnable(io_pin1);
}

bool DigitalHeader::io1_riseDetected(){
    return riseDetected(io_pin1);
}

void DigitalHeader::io1_fallEnable(){
    fallEnable(io_pin1);
}

bool DigitalHeader::io1_fallDetected(){
    return fallDetected(io_pin1);
}



void DigitalHeader::io2_asInput(){
    asInput(io_pin2);
}

void DigitalHeader::io2_asOutput(){
    asOutput(io_pin2);
}

void DigitalHeader::io2_write(uint8_t state){
    write(io_pin2,state);
}

uint8_t DigitalHeader::io2_read(){
    return read(io_pin2);
}

void DigitalHeader::io2_riseEnable(){
    riseEnable(io_pin2);
}

bool DigitalHeader::io2_riseDetected(){
    return riseDetected(io_pin2);
}

void DigitalHeader::io2_fallEnable(){
    fallEnable(io_pin2);
}

bool DigitalHeader::io2_fallDetected(){
    return fallDetected(io_pin2);
}


/**
 * Low level functions, it is provided a direct management of the IO pins.
 */

/**
 * Set the IO pin as output.
 */
void DigitalHeader::asOutput(uint8_t io_pin){
    bcm2835_gpio_fsel(io_pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(io_pin, 0);
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

void DigitalHeader::release(){    
    if(io1_dir == AS_INPUT){
        bcm2835_gpio_set_pud(io_pin1, BCM2835_GPIO_PUD_OFF);
    }else{
        bcm2835_gpio_write(io_pin1, 0);
    }
    if(io2_dir == AS_INPUT){
        bcm2835_gpio_set_pud(io_pin2, BCM2835_GPIO_PUD_OFF);
    }else{
        bcm2835_gpio_write(io_pin2, 0);
    }
    bcm_end();
}