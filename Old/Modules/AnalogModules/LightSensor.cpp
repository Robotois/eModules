/* 
 * File:   LightSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 01:52 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <cmath>
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
//    scaleFactor = 1024.0f/2048.0f;
//    basicScaleFactor = 10.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
    scaleFactor = 10.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
}

LightSensor::LightSensor(const LightSensor& orig) {
}

LightSensor::~LightSensor() {
}

void LightSensor::selectPort(uint8_t _port){
    inputPort = _port;
    switch(inputPort){
        case 0x01:
            analogModule->selectInput(ADS1015_SENSOR1,ADS1015_6144_GAIN);
            break;
        case 0x02:
            analogModule->selectInput(ADS1015_SENSOR2,ADS1015_6144_GAIN);
            break;
        case 0x03:
            analogModule->selectInput(ADS1015_SENSOR3,ADS1015_6144_GAIN);
            break;
        case 0x04:
            analogModule->selectInput(ADS1015_SENSOR4,ADS1015_6144_GAIN);
            break;
        default:
            printf("Error selecting the Analog Port...\n");
            return;
    }
}

/**
 * Get the value of the analog signal input, the input signal is in the range of
 * 0-5 volts.
 * @return 
 */
float LightSensor::getValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    return reading;
}

/**
 * The basic value is limited to the range of 0-10, and this value is given in 
 * float format.
 * @return 
 */
float LightSensor::getBasicValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (float) (input * scaleFactor);
}

uint8_t LightSensor::getScaledValue(){
    return (uint8_t)(std::round(getBasicValue()));
}

//int16_t LightSensor::getBasicScaledValue(){
//    selectPort(inputPort);
//    int16_t input = analogModule->readRawInput();
//    return (int16_t)(std::round(input * basicScaleFactor));
//}

void LightSensor::release(){
    printf("[LightSensor] => Released\n");
    analogModule->release();
    delete analogModule;
}