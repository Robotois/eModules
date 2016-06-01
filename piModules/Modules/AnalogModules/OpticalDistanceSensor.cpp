/* 
 * File:   OpticalDistanceSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 09:06 AM
 */

#include "OpticalDistanceSensor.h"
#include <stdlib.h>
#include<cmath>
#include <stdint.h>
#include<iostream>

OpticalDistanceSensor::OpticalDistanceSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
}

OpticalDistanceSensor::OpticalDistanceSensor(const OpticalDistanceSensor& orig) {
}

OpticalDistanceSensor::~OpticalDistanceSensor() {
    delete analogModule;
}

void OpticalDistanceSensor::selectPort(uint8_t _addr){
    analogModule->selectModule();
    inputPort = _addr;
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
            printf("Error selecting the Analog Channel...\n");
            exit(EXIT_FAILURE);
    }
}

float OpticalDistanceSensor::getDistance(){
//    analogModule->selectModule();
    selectPort(inputPort);
    float reading = analogModule->readInput();
////Fitness: 57928.89508794543; medianError: 1.72625422681002 ; [28.142297327584714, -1.171874995889084, -0.7541231022934074]    
    return 28.142297f*pow(reading,-1.171874f)-0.754123f;
}