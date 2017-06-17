/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PHSensor.cpp
 * Author: yovany
 * 
 * Created on January 20, 2017, 5:59 PM
 */

#include <cstdio>

#include "PHSensor.h"

PHSensor::PHSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
    slope = (0.0f-14.0f)/((0.414f+0.512)-(-0.414f+0.512));
}

PHSensor::PHSensor(const PHSensor& orig) {
}

PHSensor::~PHSensor() {
    delete analogModule;
}

void PHSensor::selectPort(uint8_t _port){
    inputPort = _port;
    switch(inputPort){
        case 0x01:
            analogModule->selectInput(ADS1015_SENSOR1,ADS1015_512_GAIN);
            break;
        case 0x02:
            analogModule->selectInput(ADS1015_SENSOR2,ADS1015_512_GAIN);
            break;
        case 0x03:
            analogModule->selectInput(ADS1015_SENSOR3,ADS1015_512_GAIN);
            break;
        case 0x04:
            analogModule->selectInput(ADS1015_SENSOR4,ADS1015_512_GAIN);
            break;
        default:
            printf("Error selecting the Analog Port...\n");
            return;
    }    
}

float PHSensor::read(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
    float phValue = slope*reading+7.0f;
    printf("Reading: %0.5f\tphValue: %0.2f\n", reading,phValue);
//    printf("phValue: %0.2f\n",phValue);
    return phValue;
}

float PHSensor::readRaw(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
//    float phValue = slope*reading+7.0f;
//    printf("Reading: %0.5f\tphValue: %0.2f\n", reading,phValue);
//    printf("phValue: %0.2f\n",phValue);
    return reading;
}