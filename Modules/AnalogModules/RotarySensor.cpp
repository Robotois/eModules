/* 
 * File:   RotarySensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 04:10 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <cmath>
#include "RotarySensor.h"

RotarySensor::RotarySensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
//    scaleFactor = 1024.0f/2048.0f;
    scaleFactor = 1024.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
    basicScaleFactor = 10.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
}

RotarySensor::RotarySensor(const RotarySensor& orig) {
}

RotarySensor::~RotarySensor() {
}

void RotarySensor::selectPort(uint8_t _port){
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

float RotarySensor::getValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    return reading;
}

//float RotarySensor::getBasicValue(){
//    selectPort(inputPort);
//    float reading = std::round(analogModule->readInput() * 100.0f)/100.0f;
//    return reading;
//}

int16_t RotarySensor::getScaledValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(std::round(input * scaleFactor));
}

int16_t RotarySensor::getBasicScaledValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(std::round(input * basicScaleFactor));
}

void RotarySensor::release(){
    printf("[RotarySensor] => Released\n");
    analogModule->release();
    delete analogModule;
}