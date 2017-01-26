/* 
 * File:   LightSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 01:52 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <math.h>
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
//    scaleFactor = 1024.0f/2048.0f;
    scaleFactor = 1024.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
    basicScaleFactor = 10.0f/1700.0f; // - usin a gain of ADS1015_6144_GAIN, 1700.0 => 5.1v
}

LightSensor::LightSensor(const LightSensor& orig) {
}

LightSensor::~LightSensor() {
    delete analogModule;
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

float LightSensor::getValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    return reading;
}

//float LightSensor::getBasicValue(){
//    selectPort(inputPort);
//    float reading = ((int16_t)(analogModule->readInput() * 100.0f))/100.0f;
//    return reading;
//}

int16_t LightSensor::getScaledValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(input * scaleFactor);
}

int16_t LightSensor::getBasicScaledValue(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(input * basicScaleFactor);
}
