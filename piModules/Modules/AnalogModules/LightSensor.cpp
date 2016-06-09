/* 
 * File:   LightSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 01:52 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
    scaleFactor = 1024.0f/2048.0f;
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

float LightSensor::getLight(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    return reading;
}

int16_t LightSensor::getScaledLight(){
    selectPort(inputPort);
    int16_t input = analogModule->readRawInput();
    return (int16_t)(input * scaleFactor);
}