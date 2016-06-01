/* 
 * File:   PCA9685.cpp
 * Author: yova
 * 
 * Created on 26 de mayo de 2016, 09:09 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include <bcm2835.h>
#include <unistd.h>

#include "PCA9685.h"

PCA9685::PCA9685(uint8_t _addr) {
    uint8_t result;
//    slave_addr = _add;
    invertedMode = false;
    
    if(_addr < 0 or _addr > 7){ // - 3 bits for custom address
        printf("Wrong slave address for the PWM Module...\n");
        exit(EXIT_FAILURE);    
    }
    
    slave_addr = PCA9685_ADDRESS | _addr;
    
    selectModule();
    // - Testing PCA9685 connection to the I2C bus
    wBuf[0] = PCA9685_MODE1;
    result = bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    if(result == 0x01){
        printf("Error reading from the PWM Device...\n");
        exit(EXIT_FAILURE);
    }
    initialize();
}

PCA9685::PCA9685(const PCA9685& orig) {
}

PCA9685::~PCA9685() {
}

void PCA9685::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_addr);
}

void PCA9685::initialize(){
    wBuf[0] = PCA9685_MODE1;
    wBuf[1] = 0x20; // - Auto increment, Normal mode, all call disabled
    
    bcm2835_i2c_write(wBuf, 2);
}

void PCA9685::setPreScale(uint8_t _pre_scale){
    uint8_t prevMode, currentMode;
    selectModule();
    
    // -- Set the PCA9685 in Sleep Mode
    wBuf[0] = PCA9685_MODE1;
    
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    prevMode = rBuf[0];
    // - Sleep mode for setting the Prescale register
    currentMode = (prevMode & 0x7F) | 0x10; // - Restart = 0, Go to sleep
    
    wBuf[0] = PCA9685_MODE1;
    wBuf[1] = currentMode;
    
    bcm2835_i2c_write(wBuf, 2);
    
    // -- Set the Prescale value
    wBuf[0] = PCA9685_PRE_SCALE;
    wBuf[1] = _pre_scale; // - Prescaler => 150Hz
  
    bcm2835_i2c_write(wBuf, 2);    
    
    // --- Set back the previous MODE status
    wBuf[0] = PCA9685_MODE1;
    wBuf[1] = prevMode;
    // - Setting back to the previous mode
    bcm2835_i2c_write(wBuf, 2);
    usleep(500); // - Wait for oscillator
    
    wBuf[0] = PCA9685_MODE1;
    wBuf[1] = prevMode | 0x80; // - Restart
    // - Restarting
    bcm2835_i2c_write(wBuf, 2);    
}

void PCA9685::setInvertedMode(){
    invertedMode = true;
}

void PCA9685::allOn(){
    selectModule();
    uint16_t on = 4096;

    if(invertedMode){
        wBuf[0] = PCA9685_ALL_ON_L;
        wBuf[1] = 0x00; 
        wBuf[2] = 0x00;
        wBuf[3] = (uint8_t)(on); 
        wBuf[4] = (uint8_t)(on>>8);
        bcm2835_i2c_write(wBuf, 5);   
    }else{
        wBuf[0] = PCA9685_ALL_ON_L;
        wBuf[1] = (uint8_t)(on); 
        wBuf[2] = (uint8_t)(on>>8);
        wBuf[3] = 0x00; 
        wBuf[4] = 0x00;
        bcm2835_i2c_write(wBuf, 5);   
    }    
}

void PCA9685::allOff(){
    selectModule();
    uint16_t off = 4096;
    if(invertedMode){
        wBuf[0] = PCA9685_ALL_ON_L;
        wBuf[1] = (uint8_t)(off); 
        wBuf[2] = (uint8_t)(off>>8);
        wBuf[3] = 0x00; 
        wBuf[4] = 0x00;
        bcm2835_i2c_write(wBuf, 5);   
    }else{
        wBuf[0] = PCA9685_ALL_ON_L;
        wBuf[1] = 0x00; 
        wBuf[2] = 0x00;
        wBuf[3] = (uint8_t)(off); 
        wBuf[4] = (uint8_t)(off>>8);
        bcm2835_i2c_write(wBuf, 5);   
    }
}

void PCA9685::setPWM(uint8_t _channel, uint16_t _pwm){
    selectModule();
    if(!(_channel >= 0 and _channel <= 15)){
        printf("Wrong selection of the PWM channel...\n");
        exit(EXIT_FAILURE);
    }

    if(invertedMode){
        if(_pwm == 0){ // - OFF state
            onTime = 4096;
            offTime = 0;
        }else{
            onTime = 0;
            offTime = 4095 - _pwm;
        }
    }else{
        if(_pwm == 0){ // - OFF state
            onTime = 0;
            offTime = 4096;
        }else{
            onTime = 0;
            offTime = _pwm;
        }
    }

    wBuf[0] = PCA9685_CH0_ON_L+(4*_channel);
    wBuf[1] = 0x00; 
//    bcm2835_i2c_write(wBuf, 2);

//    wBuf[0] = SERVO0_ON_H+(4*channel);
    wBuf[2] = 0x00;
//    result = bcm2835_i2c_write(wBuf, 2);

//    wBuf[0] = SERVO0_OFF_L+(4*channel);
    wBuf[3] = (uint8_t)offTime; 
//    result = bcm2835_i2c_write(wBuf, 2);

//    wBuf[0] = SERVO0_OFF_H+(4*channel);
    wBuf[4] = (uint8_t)(offTime >> 8);
    bcm2835_i2c_write(wBuf, 5);        
}

void PCA9685::setPWM(uint8_t _init_channel, uint8_t _channel_count, uint16_t *_pwm_array){
//    uint16_t currentPWM;
    char *_wBuf;
    selectModule();
    if(_init_channel < 0 or (_init_channel + _channel_count - 1) > 15){
        printf("Error in the amount of PWM channels to be set...\n");
        exit(EXIT_FAILURE);
    }
    
    _wBuf = new char[_channel_count*4+1];
    
    // - The initial channel address
    _wBuf[0] = PCA9685_CH0_ON_L+(4*_init_channel);
    
    for(uint8_t i = 0; i < _channel_count; i++){
        if(invertedMode){
            if(_pwm_array[i] == 0){ // - OFF state
                onTime = 4096;
                offTime = 0;
            }else{
                onTime = 0;
                offTime = 4095 - _pwm_array[i];
            }
        }else{
            if(_pwm_array[i] == 0){ // - OFF state
                onTime = 0;
                offTime = 4096;
            }else{
                onTime = 0;
                offTime = _pwm_array[i];
            }
        }
        
        _wBuf[(i*4)+1] = (uint8_t)onTime; 
        _wBuf[(i*4)+2] = (uint8_t)(onTime >> 8);
        _wBuf[(i*4)+3] = (uint8_t)offTime; 
        _wBuf[(i*4)+4] = (uint8_t)(offTime >> 8);
    }    
    bcm2835_i2c_write(_wBuf, _channel_count*4 + 1);        
}