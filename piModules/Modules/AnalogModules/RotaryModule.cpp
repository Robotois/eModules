/* 
 * File:   RotaryModule.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 04:10 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include "RotaryModule.h"

RotaryModule::RotaryModule(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
    scaleFactor = 1024.0f/2048.0f;
}

RotaryModule::RotaryModule(const RotaryModule& orig) {
}

RotaryModule::~RotaryModule() {
    delete analogModule;
}

void RotaryModule::selectPort(uint8_t _port){
    analogModule->selectModule();
    inputPort = _port;
    switch(inputPort){
        case 0x01:
            analogModule->selectInput(ADS1015_SENSOR1,ADS1015_4096_GAIN);
            break;
        case 0x02:
            analogModule->selectInput(ADS1015_SENSOR2,ADS1015_4096_GAIN);
            break;
        case 0x03:
            analogModule->selectInput(ADS1015_SENSOR3,ADS1015_4096_GAIN);
            break;
        case 0x04:
            analogModule->selectInput(ADS1015_SENSOR4,ADS1015_4096_GAIN);
            break;
        default:
            printf("Error selecting the Analog Port...\n");
            exit(EXIT_FAILURE);
    }
}

float RotaryModule::getValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    return reading;
}

int16_t RotaryModule::getScaledValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(input * scaleFactor);
}