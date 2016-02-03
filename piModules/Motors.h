/* 
 * File:   Motors.h
 * Author: yova
 *
 * Created on 26 de enero de 2016, 06:15 PM
 */

#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <bcm2835.h>

#ifndef MOTORS_H
#define	MOTORS_H
class Motors {
public:
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    uint8_t slave_address;
    uint8_t clockwise;
    uint8_t counter_clockwise;
    uint8_t stop;

    Motors();
    Motors(const Motors& orig);
    virtual ~Motors();
    
    void selectModule();
    
    void maSetup(float gearBox);
    void maControl(uint8_t control);
    void maPWM(float pwmReal);
    void maSpeed(uint16_t rpm);

    void mbSetup(float gearBox);
    void mbControl(uint8_t control);
    void mbPWM(float pwmReal);
    void mbSpeed(uint16_t rpm);
    void motorsPWM(float maPWM, float mbPWM);
    
    void maStepResponse();

    void configPause();
private:

};

#endif	/* MOTORS_H */

