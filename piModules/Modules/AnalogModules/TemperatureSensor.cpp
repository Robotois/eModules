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
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& orig) {
}

TemperatureSensor::~TemperatureSensor() {
    delete analogModule;
}

void TemperatureSensor::selectPort(uint8_t _port){
    analogModule->selectModule();
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
            exit(EXIT_FAILURE);
    }
}

float TemperatureSensor::getTemperature(){
//    analogModule->selectModule();
    selectPort(inputPort);
    float reading = analogModule->readInput();
////Fitness: 57928.89508794543; medianError: 1.72625422681002 ; [28.142297327584714, -1.171874995889084, -0.7541231022934074]    
    return reading*(25.0f/0.750f);
}