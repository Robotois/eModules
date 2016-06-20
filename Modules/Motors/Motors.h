/* 
 * File:   Motors.h
 * Author: yova
 *
 * Created on 26 de enero de 2016, 06:15 PM
 */

#ifndef MOTORS_H
#define	MOTORS_H
#include <stdint.h>
#define MOTORS_STOP 0x00

class Motors {
public:
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    uint8_t slave_address;
    static const uint8_t clockwise = 2;
    static const uint8_t counter_clockwise = 1;
    static const uint8_t stop = 0;

    Motors(uint8_t _add = 0x00);
    Motors(const Motors& orig);
    virtual ~Motors();
    
    void selectModule();
    
    void motorsSetup25D();
    void maSetup(float gearBox);
    void maControl(uint8_t control);
    void maPWM(int16_t pwmReal);
    void maSpeed(int16_t rpm);

    void mbSetup(float gearBox);
    void mbControl(uint8_t control);
    void mbPWM(int16_t pwmReal);
    void mbSpeed(int16_t rpm);
    
    void motorsControl(uint8_t maControl,uint8_t mbControl);
//    void motorsPWM(float maPWM, float mbPWM);
    void motorsPWM(int16_t maPWM, int16_t mbPWM);
    void drivePWMs(int16_t maPWM, int16_t mbPWM);
    void motorsSpeed(int16_t maSpeed, int16_t mbSpeed);
    void driveSpeeds(int16_t maSpeed,int16_t mbSpeed);
    void GetEncoderTicks(long *LeftEncodetTicks, long *RightEncoderTicks);
    void ResetEncoderCounters();
    
    void maBasicTest();
    void motorsBasicTest();
    void motorsBasicSpeedTest();
    void maFullSpeedTest();
    void maPIDResponse();

    void mbBasicTest();
    void mbFullSpeedTest();
    void mbPIDResponse();

    void configPause();
private:
    int16_t ma_pwm, mb_pwm,ma_speed,mb_speed;
    
    void constrain(int16_t *value,int16_t min, int16_t max);
    void bcm_init();
    void bcm_end();

};

#endif	/* MOTORS_H */

