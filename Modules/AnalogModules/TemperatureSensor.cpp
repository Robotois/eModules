/* 
 * File:   TempSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 03:33 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
    tempRatio = 25.0f/0.750f;
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& orig) {
}

TemperatureSensor::~TemperatureSensor() {
    delete analogModule;
}

void TemperatureSensor::selectPort(uint8_t _port){
    inputPort = _port;
    switch(inputPort){
        case 0x01:
            analogModule->selectInput(ADS1015_SENSOR1,ADS1015_2048_GAIN);
            break;
        case 0x02:
            analogModule->selectInput(ADS1015_SENSOR2,ADS1015_2048_GAIN);
            break;
        case 0x03:
            analogModule->selectInput(ADS1015_SENSOR3,ADS1015_2048_GAIN);
            break;
        case 0x04:
            analogModule->selectInput(ADS1015_SENSOR4,ADS1015_2048_GAIN);
            break;
        default:
            printf("Error selecting the Analog Port...\n");
            return;
    }
}

float TemperatureSensor::getTemperature(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
//    printf("Reading: %0.2f\n",reading);
    return reading*tempRatio;
}
