/* 
 * File:   Motors.h
 * Author: yova
 *
 * Created on 26 de enero de 2016, 06:15 PM
 */

#ifndef MOTORS_H
#define	MOTORS_H

#include <stdint.h>
#include <stdlib.h>

#define MOTORS_MOTOR1_CONN 0x01
#define MOTORS_MOTOR2_CONN 0x02
#define MOTORS_CLOCKWISE 0x02
#define MOTORS_COUNTER_CLOCKWISE 0x01
#define MOTORS_STOP 0x00
#define MOTORS_MAX_USER_SPEED (int16_t)100
#define MOTORS_MAX_SPEED (int16_t)1000

// --- Function Registers
#define MOTORS_M1_CONTROL 0x00 // Register for motor 1 control
#define MOTORS_M2_CONTROL 0x01 // Register for motor 2 control
#define MOTORS_M1_PWM 0x02 // Address of the lower byte for the PWM of motor 1
//#define MOTORS_M1_PWM_BYTE2 0x03 // Address of the upper byte for the PWM of motor 1
#define MOTORS_M2_PWM 0x04 // Address of the lower byte for the PWM of motor 2
//#define MOTORS_M2_PWM_BYTE2 0x05 // Address of the upper byte for the PWM of motor 2

class Motors {
public:
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    uint8_t slave_address;
        
    Motors(uint8_t _add = 0x00);
    Motors(const Motors& orig);
    virtual ~Motors();
    
    void selectModule();
    
    void motor1Control(uint8_t control);
    void motor2Control(uint8_t control);
    void motorsControl(uint8_t m1Control,uint8_t m2Control);

    void motor1PWM(float pwm);
    void motor2PWM(float pwm);
    void motorsPWM(float m1PWM, float m2PWM);

    void drivePWM(float m1PWM, float m2PWM);

    void release();
private:
    uint8_t leftMotor;
    uint8_t rightMotor;
    // The final integer value for PWM, this is the value that goes to the Motor
    // Module.
    int16_t realMotor1PWM, realMotor2PWM;
    
    int16_t constrainPWM(float value);
    int16_t constrain(int16_t value, int16_t min, int16_t max);
    void bcm_init();
    void bcm_end();

};

#endif	/* MOTORS_H */

