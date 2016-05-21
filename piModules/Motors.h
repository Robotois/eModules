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
    static const uint8_t clockwise = 2;
    static const uint8_t counter_clockwise = 1;
    static const uint8_t stop = 0;

    Motors();
    Motors(const Motors& orig);
    virtual ~Motors();
    
    void selectModule();
    
    void motorsSetup25D();
    void maSetup(float gearBox);
    void maControl(uint8_t control);
    void maPWM(float pwmReal);
    void maSpeed(uint16_t rpm);

    void mbSetup(float gearBox);
    void mbControl(uint8_t control);
    void mbPWM(float pwmReal);
    void mbSpeed(uint16_t rpm);
    
    void motorsControl(uint8_t maControl,uint8_t mbControl);
    void motorsPWM(float maPWM, float mbPWM);
    void motorsPWM2(int maPWM, int mbPWM);
    void drivePWMs(int maPWM, int mbPWM);
    void motorsSpeed(uint16_t maSpeed, uint16_t mbSpeed);
    void driveSpeeds(int maSpeed,int mbSpeed);
    void GetEncoderTicks(long *LeftEncodetTicks, long *RightEncoderTicks);
    void ResetEncoderCounters();
    
    void maBasicTest();
    void motorsBasicTest();
    void maFullSpeedTest();
    void maPIDResponse();

    void mbBasicTest();
    void mbFullSpeedTest();
    void mbPIDResponse();

    void configPause();
private:
    uint16_t ma_pwm, mb_pwm,ma_speed,mb_speed;
    

};

#endif	/* MOTORS_H */

