/* 
 * File:   ADS1015.cpp
 * Author: yova
 * 
 * Created on 19 de mayo de 2016, 08:29 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include <bcm2835.h>
#include<iostream>
#include<cmath>
#include <unistd.h>
#include "ADS1015.h"

ADS1015::ADS1015(uint8_t _addr) {
    uint8_t result;
    addr = _addr;
//    currentInput = 0x04;
//    bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626);
    selectModule();
    
    wBuf[0] = ADS1015_CONFIG_REG;
    result = bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    if(result == 0x01){
        printf("Error reading from the Analog Module...\n");
        exit(EXIT_FAILURE);
    }
}

ADS1015::ADS1015(const ADS1015& orig) {
}

ADS1015::~ADS1015() {
}

void ADS1015::selectModule(){
    bcm2835_i2c_setSlaveAddress(addr);
}

/**
 * Set the input port to be read and the gain. It is recomended that the gain is selected 
 * according to the maximum input voltage for the given input address, this way
 * we'll obtain a good resolution.
 * @param _inputAdd
 * @param _gain
 */
void ADS1015::selectInput(uint8_t _inputAdd, uint8_t _gain){
    selectModule();
    inputAdd = _inputAdd;
    inputGain = _gain;

    if(!(inputAdd >= 0x04 and inputAdd <= 0x07)){ // - Seleccion de entrada individual
        printf("Invalid Input...\n");
        exit(EXIT_FAILURE);
    }

    if(!(inputGain >= 0x01 and inputGain <= 0x03)){ // - Seleccion de entrada individual
        printf("Invalid Gain...\n");
        exit(EXIT_FAILURE);
    }
    switch(inputGain){
        case ADS1015_1024_GAIN:
            resolution = 1.024f/2048.0f; // - volts/(11 bits)
            break;
        case ADS1015_2048_GAIN:
            resolution = 2.048f/2048.0f; // - volts/(11 bits)
            break;
        case ADS1015_4096_GAIN:
            resolution = 4.096f/2048.0f; // - volts/(11 bits)
            break;
    }
    
    wBuf[0] = ADS1015_CONFIG_REG;
    // - The upper Byte
    wBuf[1] = (uint8_t)(inputAdd << 4) | (uint8_t)(inputGain << 1);
    // - Lower Byte => 128 SPS, Disble Comparator
    wBuf[2] = (uint8_t)(ADS1015_128SPS<<4) | 0x03;
    
    bcm2835_i2c_write(wBuf, 3);
    usleep(50000);
}

int16_t ADS1015::readRawInput(){
    selectModule();
    uint16_t input = 0x00;
    
    wBuf[0] = ADS1015_CONV_REG; // - Registro de conversion
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    
    input = (uint16_t)(rBuf[0] << 8) |(rBuf[1]);
    input = input >> 4;
    
    return fullRangeMeas(input);
}

int16_t ADS1015::fullRangeMeas(uint16_t reading){
    if(reading > 0x07FF)
        return -((4096 - reading)+1);
    else
        return (int16_t)reading;
}


/**
 * Returns the current input reading in volts.
 * @return 
 */
float ADS1015::readInput(){
    int16_t input = readRawInput();
    
    return input*resolution;
}
