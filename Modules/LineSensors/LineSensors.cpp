/* 
 * File:   LineFinder.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 12:47 PM
 */

#include<bitset>
#include <stdint.h>
#include <stdlib.h>
#include<iostream>

#include "LineSensors.h"

LineSensors::LineSensors(uint8_t _addr) {
    mcp = new MCP23008(_addr);
    initialize();
}

LineSensors::LineSensors(const LineSensors& orig) {
}

LineSensors::~LineSensors() {
    mcp->digitalWrite(LINESENSORS_ENABLE,MCP23008_LOW); //Disable the sensors    
    delete mcp;
}

void LineSensors::initialize(){
    // Sensors are ordered from left to right
    _io_pins[0] = LINESENSORS_SENSOR1;
    _io_pins[1] = LINESENSORS_SENSOR2;
    _io_pins[2] = LINESENSORS_SENSOR3;
    _io_pins[3] = LINESENSORS_SENSOR4;
    _io_pins[4] = LINESENSORS_SENSOR5;
    _io_pins[5] = LINESENSORS_SENSOR6;
    _io_pins[6] = LINESENSORS_ENABLE;
    
    mcp->setDir(_io_pins,MCP23008_INPUT,6); //Sensor pins as inputs
    mcp->setPullUp(_io_pins,MCP23008_PULL_UP_EN,6); //Pull-Ups enabled for sensor pins
    mcp->setDir(LINESENSORS_ENABLE,MCP23008_OUTPUT); //Enable pin as output
    mcp->digitalWrite(LINESENSORS_ENABLE,MCP23008_HIGH); //Enable the sensors  
    
    background = LINESENSORS_WHITE_BACKGROUND; // Default background
}

uint8_t LineSensors::readSensors(){
    if(background == LINESENSORS_WHITE_BACKGROUND)
        return mcp->readGPIO()&0x1F;
    else
        return (~mcp->readGPIO()) & 0x1F;
}

uint8_t LineSensors::readSensor(uint8_t _sensor){
    uint8_t _sensorsReading;
    if(_sensor > LINESENSORS_SENSOR6 ){
        printf("Error reading the Line Sensor...\n");
        return 0x00;
    }
    
    _sensorsReading = readSensors();
    return (_sensorsReading >> _sensor) & 0x01;
}

float LineSensors::readLine(){
    uint8_t inputs = readSensors();
//    printf("Sensors: 0x%02X \n",inputs);
    
    if(inputs == 0x00)
        return -1.0;
    
    int cumSum = 0;
    float avg = 0;
    
    for(uint8_t i = 0; i < 5; i++){
        if(inputs & (1<<i)){
            avg += 100 * (i*100);
            cumSum += 100;
        }
    }
    avg = avg/cumSum;    
//    printf("%0.2f\n",avg);
    return avg;
}

void LineSensors::setBackground(uint8_t _bg){
    background = _bg;
}