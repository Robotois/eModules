/* 
 * File:   TempSensor.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 03:33 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t _addr) {
    analogModule = new ADS1015(_addr);
    tempRatio = 25.0f/0.750f;
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& orig) {
}

TemperatureSensor::~TemperatureSensor() {
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

/**
 * Temeperatura actual del sensor en grados centigrados. Se proporciona la maxima
 * resolucion que se puede obtener, en este caso son 11 bits para valores mayores que 0
 * grados.
 * @return 
 */
float TemperatureSensor::getValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
//    printf("Reading: %0.2f\n",reading);
    return reading*tempRatio;
}

///**
// * Temperatura en grados centigrados, pero se acota la resolucion a dos decimales.
// * Con esto se obtiene una medicion "basica", puede ser usada para mostrar la temperatura
// * en al display LCD por ejemplo
// * @return 
// */
//float TemperatureSensor::getBasicValue(){
//    selectPort(inputPort);
//    float reading = analogModule->readInput();
////    printf("Reading: %0.2f\n",reading);
//    return std::round( (reading*tempRatio) * 100.0f)/100.0f;
//}

/**
 * Se obtiene la Temperatura en grados centigrados, pero solo se obtiene la parte entera
 * de la medicion, esta medicion es aun mas simple que getBasicValue.
 * @return 
 */
int16_t TemperatureSensor::getIntValue(){
    selectPort(inputPort);
    float reading = analogModule->readInput();
//    printf("Reading: %0.2f\n",reading);
    return (int16_t)(std::round(reading*tempRatio));
}

void TemperatureSensor::release(){
    printf("[TemperatureSensor] => Released\n");
    analogModule->release();
    delete analogModule;
}