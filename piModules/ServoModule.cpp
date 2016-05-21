/* 
 * File:   Servos.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "ServoModule.h"
#include<cmath>

ServoModule::ServoModule() {
    slave_address = 0x41;
    centerOffTime = (maxOnTime - minOnTime)/2.0;
    angleTimeRatio = (maxOnTime - minOnTime)/165.0;
    onTime = delay;
}

ServoModule::ServoModule(const ServoModule& orig) {
}

ServoModule::~ServoModule() {
}

void ServoModule::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_address);    
}

/**
 * Inicializacion del modulo de Servos, la direccion por default es 0x40, la cual 
 * se establece en el constructor.
 */
void ServoModule::initialize(){
    uint8_t prevMode, currentMode;
    selectModule();    
    // - Set MODE2 register
    wBuf[0] = MODE2;
    wBuf[1] = 0x04; 
    
    result = bcm2835_i2c_write(wBuf, 2);
//    printf("Set MODE2 Reg, Write Result = %d\n", result);

    // - Set MODE1 register
//    len = 2;
    wBuf[0] = MODE1;
    wBuf[1] = 0x01; // - Normal mode, all call
    
    result = bcm2835_i2c_write(wBuf, 2);
//    printf("Set MODE1 Reg, Write Result = %d\n", result);
    
    // - Wait for oscillator
    usleep(500);
    
    // - Reset a todos los servos
    wBuf[0] = ALL_SERVOs_ON_L;
    wBuf[1] = 0; 
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = ALL_SERVOs_ON_H;
    wBuf[1] = 0;
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = ALL_SERVOs_OFF_L;
    wBuf[1] = 0; 
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = ALL_SERVOs_OFF_H;
    wBuf[1] = 0;
    result = bcm2835_i2c_write(wBuf, 2);   

    // - Set PRE_SCALE register
    wBuf[0] = MODE1;
    
    result = bcm2835_i2c_write(wBuf,1);
    result = bcm2835_i2c_read(rBuf,1);
    prevMode = rBuf[0];
    // - Sleep mode for setting the Prescale register
    currentMode = (prevMode & 0x7F) | 0x10; // - Restart = 0, Go to sleep
    
    wBuf[0] = MODE1;
    wBuf[1] = currentMode;
    
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = PRE_SCALE;
    wBuf[1] = 0x7C; // - Prescaler => 50Hz
  
    result = bcm2835_i2c_write(wBuf, 2);
//    printf("Set Prescale Reg, Write Result = %d\n", result);
    
    wBuf[0] = MODE1;
    wBuf[1] = prevMode;
    // - Setting back to the previous mode
    result = bcm2835_i2c_write(wBuf, 2);
    usleep(500); // - Wait for oscillator
    
    wBuf[0] = MODE1;
    wBuf[1] = prevMode | 0x80; // - Restart
    // - Restarting
    result = bcm2835_i2c_write(wBuf, 2);    
    
}

/**
 * Establece el angulo de un Servo en particular.
 * @param servoNumber: Numero del servo => 0-7.
 * @param degree: Angulo en grados centigrados => [-82.5 - 82.5].
 * para un angulo de 0° el servo apunta verticalmente hacia arriba.
 */
void ServoModule::setAngle(uint8_t servoNumber, float degree){
    if(degree> 100.0){
        degree = 100;
    }
    if(degree < -100.0){
        degree = -100;
    }
//    uint8_t offset = servoNumber - 1;
    offTime = delay + minOnTime + centerOffTime + degree*angleTimeRatio;
    wBuf[0] = SERVO0_ON_L+(4*servoNumber);
    wBuf[1] = onTime & 0xFF; 
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = SERVO0_ON_H+(4*servoNumber);
    wBuf[1] = onTime >> 8;
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = SERVO0_OFF_L+(4*servoNumber);
    wBuf[1] = offTime & 0xFF; 
    result = bcm2835_i2c_write(wBuf, 2);

    wBuf[0] = SERVO0_OFF_H+(4*servoNumber);
    wBuf[1] = offTime >> 8;
    result = bcm2835_i2c_write(wBuf, 2);    
}