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

using namespace std;

void i2c_init();
void i2c_end();
void LineFollower();

/*
 * 
 */
int main(int argc, char** argv) {
    i2c_init();

    LineFollower();
    
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
        if(currentPWM < maxPWM){
            currentPWM += 0.1;
        }
    }
    motorModule->selectModule();
    motorModule->maControl(motorModule->stop);
    motorModule->mbControl(motorModule->stop);
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