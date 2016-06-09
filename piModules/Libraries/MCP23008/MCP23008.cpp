/* 
 * File:   MCP23008.cpp
 * Author: yova
 * 
 * Created on 27 de mayo de 2016, 07:57 PM
 */
#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <bcm2835.h>

#include "MCP23008.h"

MCP23008::MCP23008(uint8_t _addr) {
    uint8_t result;
    
    if(_addr > 7){ // - 3 bits for custom address
        printf("Wrong slave address for the Digital IO Module...\n");
        return;    
    }
    
    slave_addr = MCP23008_ADDRESS | _addr;
    
    selectModule();
    // - Read from the MCP23008 device to make sure it is connected
    wBuf[0] = MCP23008_IODIR;
    result = bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    if(result == 0x01){
        printf("Error reading from the Digital IO Device...\n");
        exit(EXIT_FAILURE);
    }
}

MCP23008::MCP23008(const MCP23008& orig) {
}

MCP23008::~MCP23008() {
}

void MCP23008::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_addr);
}

void MCP23008::setDir(uint8_t _pin, uint8_t dir){
    uint8_t io_dir_mask;
    selectModule();
    
    // - Read the current configuration of the IO direction
    wBuf[0] = MCP23008_IODIR;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    io_dir_mask = rBuf[0];
    
    if(_pin > 7 ){
        printf("Error assigning the IO direction in the Digital IO Device...\n");
        exit(EXIT_FAILURE);
    }

    if(dir == MCP23008_INPUT){
        io_dir_mask |= 1 << _pin;
    }else{
        io_dir_mask &= ~(1 << _pin);
    }

    wBuf[1] = io_dir_mask;
    bcm2835_i2c_write(wBuf,2);
}

void MCP23008::setDir(uint8_t* pin_array, uint8_t dir, uint8_t pin_count){
    uint8_t io_dir_mask;
    selectModule();
    
    // - Read the current configuration of the IO direction
    wBuf[0] = MCP23008_IODIR;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    io_dir_mask = rBuf[0];
    
    for(uint8_t i = 0; i < pin_count; i++){
        if(pin_array[i] > 7 ){
            printf("Error assigning the IO direction in the Digital IO Device...\n");
            exit(EXIT_FAILURE);
        }
        
        if(dir == MCP23008_INPUT){
            io_dir_mask |= 1 << pin_array[i];
        }else{
            io_dir_mask &= ~(1 << pin_array[i]);
        }
    }
    wBuf[1] = io_dir_mask;
    bcm2835_i2c_write(wBuf,2);
}

void MCP23008::setPullUp(uint8_t* pin_array, uint8_t pu, uint8_t pin_count){
    uint8_t pu_mask;
    selectModule();
    
    // - Read the current configuration of the IO direction
    wBuf[0] = MCP23008_GPPU;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    pu_mask = rBuf[0];
    
    for(uint8_t i = 0; i < pin_count; i++){
        if(pin_array[i] > 7 ){
            printf("Error setting pull-up resistor in the Digital IO Device...\n");
            exit(EXIT_FAILURE);
        }
        
        if(pu == MCP23008_PULL_UP_EN){
            pu_mask |= 1 << pin_array[i];
        }else{
            pu_mask &= ~(1 << pin_array[i]);
        }
    }
    wBuf[1] = pu_mask;
    bcm2835_i2c_write(wBuf,2);    
}

uint8_t MCP23008::readGPIO(){
    selectModule();
    wBuf[0] = MCP23008_GPIO;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    return  rBuf[0];
}

void MCP23008::writeGPIO(uint8_t gpio){
    selectModule();
    wBuf[0] = MCP23008_GPIO;
    wBuf[1] = gpio;
    bcm2835_i2c_write(wBuf,2);
}

void MCP23008::digitalWrite(uint8_t pin, uint8_t val){
    uint8_t io_mask;

    if(pin > 7 ){
        printf("Error writing the IO status from the Digital IO Device...\n");
        exit(EXIT_FAILURE);
    }
    
    // - Read the current configuration of the IO direction
    io_mask = readGPIO();
    
    if(val == MCP23008_HIGH){
        io_mask |= 1 << pin;
    }else{
        io_mask &= ~(1 << pin);
    }

    writeGPIO(io_mask);    
}

uint8_t MCP23008::digitalRead(uint8_t pin){
    uint8_t io_mask;

    if(pin > 7 ){
        printf("Error reading the IO status from the Digital IO Device...\n");
        exit(EXIT_FAILURE);
    }
    
    // - Read the current configuration of the IO direction
    io_mask = readGPIO();
    return (io_mask >> pin) & 0x01;
}

void MCP23008::writeMultiGPIO(uint8_t* pin_array, uint8_t *pin_data, uint8_t pin_count){
    uint8_t io_mask;
    
    // - Read the current configuration of the IO direction
    io_mask = readGPIO();
    
    for(uint8_t i = 0; i < pin_count; i++){
        if(pin_array[i] > 7 ){
            printf("Error writing IO output to the Digital IO Device...\n");
            exit(EXIT_FAILURE);
        }
        
        if(pin_data[i] == MCP23008_HIGH){
            io_mask |= 1 << pin_array[i];
        }else{
            io_mask &= ~(1 << pin_array[i]);
        }
    }
    writeGPIO(io_mask);    
}

void MCP23008::writeMultiGPIO(uint8_t* pin_array, uint8_t pin_data, uint8_t pin_count){
    uint8_t io_mask;
    
    // - Read the current configuration of the IO direction
    io_mask = readGPIO();
    
    for(uint8_t i = 0; i < pin_count; i++){
        if(pin_array[i] > 7 ){
            printf("Error writing IO output to the Digital IO Device...\n");
            exit(EXIT_FAILURE);
        }
        
        io_mask &= ~(1 << pin_array[i]); // - Clear current bit
        // Two steps: Obtain the value of the current bit, and set such value to the current bit
        io_mask |= ((pin_data >> pin_array[i]) & 0x01) << pin_array[i];
    }
    writeGPIO(io_mask);    
}