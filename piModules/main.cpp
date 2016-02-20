/* 
 * File:   main.cpp
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:08 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
#include <math.h>
#include "Motors.h"
#include "LineSensorModule.h"
#include "ServoModule.h"
#include "LineFinder.h"

#include <iostream>
#include <armadillo>


using namespace std;
using namespace arma;

void i2c_init();
void i2c_end();
void LineFollower();
void AccelGyroTest();
int fullRange(uint16_t reading);
void armadilloTest();

/*
 * 
 */
int main(int argc, char** argv) {
    i2c_init();

//    LineFollower();
//    AccelGyroTest();
    armadilloTest();
    
    i2c_end();    

    return 0;
}

void LineFollower(){
    float lineSensors,prevLineSensors,currentError,prevError = 0,
            maxPWM = 65,currentPWM = 15, maPWM, mbPWM, // - Default 25% PWM
            kp = 1,ki = 0.001,kd = 10,integral = 0,
            powerDifference = 0,sampleTime = 1/1000.0; // - 10[ms]
        
    Motors *motorModule = new Motors();
    motorModule->maPWM(0); // - Left Motor
    motorModule->mbPWM(0); // - Left Motor
    motorModule->maControl(motorModule->counter_clockwise); // - Left Motor
    motorModule->mbControl(motorModule->clockwise); // - Right Motor
    
    LineSensorModule *lineModule = new LineSensorModule();
    lineModule->initialize();
    
    uint16_t i = 0;
    maPWM = currentPWM;
    mbPWM = currentPWM;
    sleep(2);
    while(i<7500){
        lineModule->selectModule();
        lineSensors = lineModule->readLine();
        if(lineSensors == -1.0){
            lineSensors = prevLineSensors;
        }
//        printf("Inputs: 0x%02X\n",inputs);
//        lineFinder->curveMeasurements(inputs);
//        leftSpeed = lineFinder->leftRPMSpeed();
//        printf("Left Speed: %d, ",leftSpeed);
//        rightSpeed = lineFinder->rightRPMSpeed();
//        printf("Right Speed: %d\n",rightSpeed);
        currentError = lineSensors - 250;
        prevLineSensors = lineSensors;
//        printf("%0.2f",lineSensors);

        // - PID Control
        integral += currentError;
        powerDifference = currentError*kp + integral*ki + (currentError-prevError)*kd;
        prevError = currentError;
        
//        printf("PowerDifference: %0.5f\n",powerDifference);
        
        if(powerDifference > currentPWM){
            powerDifference = currentPWM;
        }
        if(powerDifference < -currentPWM){
            powerDifference = -currentPWM;
        }

        if(powerDifference < 0.0){ // - Girar a la izquierda
            maPWM = currentPWM + powerDifference; // - Decrease power
            mbPWM = currentPWM;
        }else{
            maPWM = currentPWM;
            mbPWM = currentPWM - powerDifference; // - Decrease Power
        }
//        printf("PowerDifference: %0.5f, maPWM: %0.2f, mbPWM: %0.2f\n",powerDifference,maPWM,mbPWM);
        motorModule->selectModule();
        motorModule->motorsPWM(maPWM,mbPWM);
        // - 1[ms] de muestreo
        usleep(1000);
        i++;
        // - Slow init speed, gradually increase it to the maximum value
        if(currentPWM < maxPWM){
            currentPWM += 0.1;
        }
    }
    motorModule->selectModule();
    motorModule->maControl(motorModule->stop);
    motorModule->mbControl(motorModule->stop);
}

void AccelGyroTest(){
    /** Gyro Full-Scale Range
     * FS_SEL=0 => ±250º/s
     * FS_SEL=1 => ±500º/s
     * FS_SEL=2 => ±1000º/s
     * FS_SEL=3 => ±2000º/s
     * 
     * Accel Full-Scale Range
     * AFS_SEL=0 => ±2 g
     * AFS_SEL=1 => ±4 g
     * AFS_SEL=2 => ±8 g
     * AFS_SEL=3 => ±16 g
     */
    uint8_t GYRO_FS_SEL = 0,ACCEL_FS_SEL = 0;
    static const float gyroScaleFactors[] = {131,65.5,32.8,16.4},
            accelScaleFactors[] = {16384,8192,4096,2048};
    // - Registers
    static const uint8_t PWR_MGMT_1 = 0x6B,CONFIG = 0x1A,
            GYRO_CONFIG = 0x1B, ACCEL_CONFIG = 0x1C,
            ACCEL_XOUT_H = 0x3B, ACCEL_XOUT_L = 0x3C, ACCEL_YOUT_H = 0x3D, 
            ACCEL_YOUT_L = 0x3E, ACCEL_ZOUT_H = 0x3F, ACCEL_ZOUT_L = 0x40,
            GYRO_XOUT_H = 0x43, GYRO_XOUT_L = 0x44, GYRO_YOUT_H = 0x45, 
            GYRO_YOUT_L = 0x46, GYRO_ZOUT_H = 0x47, GYRO_ZOUT_L = 0x48;
    
    uint8_t result;
    
    // - MPU6050_init
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    
    bcm2835_i2c_setSlaveAddress(0x68);
    
    // - Clear sleep bit
    wBuf[0] = PWR_MGMT_1;
    wBuf[1] = 0x00;
    result = bcm2835_i2c_write(wBuf, 2);
    printf("PWR Config Result: %d\n",result);
    
    wBuf[0] = CONFIG;
    wBuf[1] = 0x00;
    result = bcm2835_i2c_write(wBuf, 2);
    printf("Config Result: %d\n",result);
    
    // - Burst Write Sequence
//    GYRO_FS_SEL = 0;
    wBuf[0] = GYRO_CONFIG; // - Gyro and Accel config registers have consecutive addresses
    wBuf[1] = GYRO_FS_SEL;
    wBuf[2] = ACCEL_FS_SEL;
    result = bcm2835_i2c_write(wBuf, 3);
    printf("AccelGyro Config Result: %d\n",result);
    
    // - Accel measurements (Burst Read Sequence)
    int accelXOut, accelYOut,accelZOut;
    float scaleFactor = accelScaleFactors[ACCEL_FS_SEL];
    wBuf[0] = ACCEL_XOUT_H; // - Initial register address
    bcm2835_i2c_write(wBuf, 1);
    result = bcm2835_i2c_read(rBuf, 6); // - 
    printf("Accel Measurement Status: %d\n",result);
    
    accelXOut = fullRange((rBuf[0] << 8) | rBuf[1]);
    accelYOut = fullRange((rBuf[2] << 8) | rBuf[3]);
    accelZOut = fullRange((rBuf[4] << 8) | rBuf[5]);
    printf("AccelX => %d; Scaled: %0.5f\n",accelXOut,accelXOut/scaleFactor);
    printf("AccelY => %d; Scaled: %0.5f\n",accelYOut,accelYOut/scaleFactor);
    printf("AccelZ => %d; Scaled: %0.5f\n",accelZOut,accelZOut/scaleFactor);
    
    // - Gyro measurements (Burst Read Sequence)
    int gyroXOut, gyroYOut,gyroZOut;
    scaleFactor = gyroScaleFactors[GYRO_FS_SEL];
    wBuf[0] = GYRO_XOUT_H; // - Initial register address
    bcm2835_i2c_write(wBuf, 1);
    result = bcm2835_i2c_read(rBuf, 6); // - 
    printf("Gyro Measurement Status: %d\n",result);
    
    gyroXOut = fullRange((rBuf[0] << 8) | rBuf[1]);
    gyroYOut = fullRange((rBuf[2] << 8) | rBuf[3]);
    gyroZOut = fullRange((rBuf[4] << 8) | rBuf[5]);
    printf("GyroX => %d; Scaled: %0.5f\n",gyroXOut,gyroXOut/scaleFactor);
    printf("GyroY => %d; Scaled: %0.5f\n",gyroYOut,gyroYOut/scaleFactor);
    printf("GyroZ => %d; Scaled: %0.5f\n",gyroZOut,gyroZOut/scaleFactor);
}

int fullRange(uint16_t reading){
    if(reading >= 0x8000)
        return -((65535 - reading)+1);
    else
        return (int)reading;
}

void armadilloTest(){
    mat A = randu<mat>(4,5);
    mat B = randu<mat>(4,5);
  
    cout << A*B.t() << endl;  
}

void kalmanTest(uint16_t dutation, float dt){
    float measnoise = 10, accelnoise = 0.2;
    mat A = []
}

void i2c_init(){
    // - 400kHz aproximadamente...
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_626;
    // - La direccion del esclavo se establece en cada modulo
//    uint8_t slave_address = 0x10;

    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }
    
    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
//    fprintf(stderr, "Clock divider set to: %d\n", clk_div);
//    fprintf(stderr, "Slave address set to: %d\n", slave_address);    
}

void i2c_end(){
    bcm2835_i2c_end();
    bcm2835_close();    
}