/* 
 * File:   Robotina.h
 * Author: yova
 *
 * Created on 26 de abril de 2016, 05:22 PM
 */

#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include<cstdint>
#include <cmath>
#include <chrono>

#include "Motors.h"
#include "AccelGyroModule.h"
#include <bcm2835.h>
#include "Libraries/Timer/AccurateTiming.h"

#ifndef ROBOTINA_H
#define	ROBOTINA_H

#define RAD_TO_DEG 180.0f/M_PI

#define LCD_Pin1 1
#define LCD_Pin2 0
#define LCD_Pin3 14
#define LCD_Pin4 15
#define LCD_Pin5 16
#define LCD_Pin6 17

#define c_RightEncoderInterrupt 0
#define c_RightEncoderPinA 2
#define c_RightEncoderPinB 4

#define c_LeftEncoderInterrupt 1
#define c_LeftEncoderPinA 3
#define c_LeftEncoderPinB 12


#define ThrottlePin 5
#define SteeringPin  6

#define MotorR_B 7
#define MotorR_A 8
#define MotorR_PWM 9

#define MotorL_PWM 10
#define MotorL_A 11
#define MotorL_B 13

#define buttonPin A7
#define voltSensePin A6

#define LeftEncoderIsReversed

//#define DEG_PER_COUNT 0.75f  // 480 Counts per Revolution
#define DEG_PER_COUNT 0.22049f  // 1632.67 Counts per Revolution
#define VOLT_PER_COUNT 0.01465f  // 5 V * (30 kOhm)/(10 kOhm) / 1024

#define THROTTLE_FLAG 1
#define STEERING_FLAG 2
#define LEFTENC_FLAG 4
#define RIGHTENC_FLAG 8

#define DT 5000 // 5 msec time step
#define FHz 200 // Sample Rate

/*
 *  Control Gains
 */
#define PWMFREQ 10000
#define K_p 15.0f
#define K_i 50.0f
#define K_d 0.25f
#define wheelPosGain 0.0015f
#define wheelRateGain 0.003f
#define Kp_Rotation 0.1f

//#define PitchCalOffsetDefault -2.0f
#define PitchCalOffsetDefault 1.0f

class Robotina {
public:
    Robotina();
    Robotina(const Robotina& orig);
    virtual ~Robotina();
    
    void setup();
    void loop();
private:


    //    LiquidCrystal lcd(LCD_Pin1, LCD_Pin2, LCD_Pin3, LCD_Pin4, LCD_Pin5, LCD_Pin6);

    volatile uint8_t bUpdateFlagsShared;
    volatile uint16_t _ThrottleInShared;
    volatile uint16_t _SteeringInShared;
    uint32_t ThrottleStart;
    uint32_t SteeringStart;

    // Quadrature encoders
    // Left encoder
    volatile bool _LeftEncoderBSet;
    volatile long _LeftEncoderTicks = 0;

    // Right encoder
    volatile bool _RightEncoderBSet;
    volatile long _RightEncoderTicks = 0;

//    uint32_t LastTime = 0;
    bool layingDown = true; // Use to indicate if the robot is laying down

    float MotorScaleFactor = 0.01f;
    bool RechargeBattery = 0;

    // Gyro Address
    const int MPU = 0x68; // I2C address of the MPU-6050
    uint8_t i2cBuffer[14];

    float PitchEst, BiasEst;

    float gyroXzero;
    float PitchCalOffset;
    float IntState = 0;  // Integral State

    float voltageFilt = 0;    

    char rBuf[16]; // - Max length
    char wBuf[16]; // - Max length
        
    
    float KalmanFilter(float PitchMeas, float RateMeas);
    bool calibrateGyro();
    bool checkMinMax(int16_t *array, uint8_t length, int16_t maxDifference);
    float constrain(float value, float min, float max);
    
    
    
    uint8_t debugButton,stopButton;
    uint8_t accelGyroAddress,result;
    Motors *motorModule;
    AccelGyroModule *accelGyro;
};

#endif	/* ROBOTINA_H */

