/* 
 * File:   Servos.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "Servos.h"
#include<cmath>
#include <stdint.h>

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

//void Servos::selectModule(){
//    bcm2835_i2c_setSlaveAddress(slave_address);    
//}

/**
 * Inicializacion del modulo de Servos, la direccion por default es 0x40, la cual 
 * se establece en el constructor.
 */
//void Servos::initialize(){
//    uint8_t prevMode, currentMode;
//    selectModule();    
//    // - Set MODE2 register
//    wBuf[0] = MODE2;
//    wBuf[1] = 0x04; 
//    
//    result = bcm2835_i2c_write(wBuf, 2);
////    printf("Set MODE2 Reg, Write Result = %d\n", result);
//
//    // - Set MODE1 register
////    len = 2;
//    wBuf[0] = MODE1;
//    wBuf[1] = 0x01; // - Normal mode, all call
//    
//    result = bcm2835_i2c_write(wBuf, 2);
////    printf("Set MODE1 Reg, Write Result = %d\n", result);
//    
//    // - Wait for oscillator
//    usleep(500);
//    
//    // - Reset a todos los servos
//    wBuf[0] = ALL_SERVOs_ON_L;
//    wBuf[1] = 0; 
//    result = bcm2835_i2c_write(wBuf, 2);
//
//    wBuf[0] = ALL_SERVOs_ON_H;
//    wBuf[1] = 0;
//    result = bcm2835_i2c_write(wBuf, 2);
//
//    wBuf[0] = ALL_SERVOs_OFF_L;
//    wBuf[1] = 0; 
//    result = bcm2835_i2c_write(wBuf, 2);
//
//    wBuf[0] = ALL_SERVOs_OFF_H;
//    wBuf[1] = 0;
//    result = bcm2835_i2c_write(wBuf, 2);   
//
//    // - Set PRE_SCALE register
//    wBuf[0] = MODE1;
//    
//    result = bcm2835_i2c_write(wBuf,1);
//    result = bcm2835_i2c_read(rBuf,1);
//    prevMode = rBuf[0];
//    // - Sleep mode for setting the Prescale register
//    currentMode = (prevMode & 0x7F) | 0x10; // - Restart = 0, Go to sleep
//    
//    wBuf[0] = MODE1;
//    wBuf[1] = currentMode;
//    
//    result = bcm2835_i2c_write(wBuf, 2);
//
//    wBuf[0] = PRE_SCALE;
//    wBuf[1] = 0x7C; // - Prescaler => 50Hz
//  
//    result = bcm2835_i2c_write(wBuf, 2);
////    printf("Set Prescale Reg, Write Result = %d\n", result);
//    
//    wBuf[0] = MODE1;
//    wBuf[1] = prevMode;
//    // - Setting back to the previous mode
//    result = bcm2835_i2c_write(wBuf, 2);
//    usleep(500); // - Wait for oscillator
//    
//    wBuf[0] = MODE1;
//    wBuf[1] = prevMode | 0x80; // - Restart
//    // - Restarting
//    result = bcm2835_i2c_write(wBuf, 2);    
//    
//}

/**
 * Establece el angulo de un Servo en particular.
 * @param servoNumber: Numero del servo => 0-7.
 * @param degree: Angulo en grados centigrados => [-82.5 - 82.5].
 * para un angulo de 0° el servo apunta verticalmente hacia arriba.
 */
void Servos::setAngle(uint8_t servoNumber, float degree){
    if(degree > maxTravel){
        degree = maxTravel;
    }
    if(degree < minTravel){
        degree = minTravel;
    }

    offTime = centerOffTime + degree*angleTimeRatio;
    pwmModule->setPWM(servoNumber,offTime);
}