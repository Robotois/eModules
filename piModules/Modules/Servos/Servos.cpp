/* 
 * File:   Servos.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "Servos.h"
#include<cmath>
#include <stdint.h>
#include <stdlib.h>
#include<iostream>

Servos::Servos(uint8_t _addr) {
    pwmModule = new PCA9685(_addr);
    pwmModule->setPreScale(0x7C); // - Prescaler => 50Hz
    
//    slave_address = 0x41;
    halfOffTime = (uint16_t)((maxOnTime - minOnTime)/2.0f);
    maxTravel = 90.0f;
    minTravel = -90.0f;
    angleTimeRatio = (float)(halfOffTime/maxTravel);
    onTime = 0;
    centerOffTime = 307; // => 1500us
}

Servos::Servos(const Servos& orig) {
}

Servos::~Servos() {
    delete pwmModule;
}

/**
 * Establece el angulo de un Servo en particular.
 * @param servoNumber: Numero del servo => 0-7.
 * @param degree: Angulo en grados centigrados => [-82.5 - 82.5].
 * para un angulo de 0° el servo apunta verticalmente hacia arriba.
 */
void Servos::setAngle(uint8_t servoNumber, float degree){
    constrain(&degree,minTravel,maxTravel);
    offTime = centerOffTime + degree*angleTimeRatio;
    if(servoNumber <1 and servoNumber > 6){
        printf("Wrong Channel Selection for the PWM Module...\n");
        exit(EXIT_FAILURE);    
    }
    pwmModule->setPWM(servoNumber-1,offTime);
}

void Servos::constrain(float* value, float min, float max){
    if(*value > max){
        *value = max;
        return;
    }
    
    if(*value < min){
        *value = min;
        return;
    }    
}