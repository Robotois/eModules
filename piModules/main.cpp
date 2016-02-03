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
void lineModuleTest();
float maxMinPWM(float currentPWM, float maxPWM,float minPWM);

/*
 * 
 */
int main(int argc, char** argv) {
    i2c_init();
//    Motors *motorModule = new Motors();
//    motorModule->selectModule();
////    motorModule->maSetup(51.45);
////    motorModule->mbSetup(51.45);
////    motorModule->maSpeed(25);
//    motorModule->maControl(motorModule->counter_clockwise); // - Left Motor
//    motorModule->mbControl(motorModule->clockwise); // - Right Motor
////    motorModule->maPWM(50);
//    motorModule->motorsPWM(0,25);
//    sleep(2);
//    motorModule->motorsPWM(25,50);
//    sleep(2);
//    motorModule->motorsPWM(50,75);
//    sleep(2);
//    motorModule->motorsPWM(75,75);
//    sleep(2);
//    motorModule->motorsPWM(75,50);
//    sleep(2);
//    motorModule->motorsPWM(50,25);
//    sleep(2);
//    motorModule->motorsPWM(25,0);
//    sleep(2);
//    motorModule->motorsPWM(0,0);
//    LineSensorModule *lineModule = new LineSensorModule();
//    lineModule->initialize();
//    lineModule->readLine();

    lineModuleTest();
    
//    ServoModule *servoModule = new ServoModule();
//    
//    servoModule->initialize();
//    servoModule->selectModule();
//    uint8_t counter = 0;
//    while(counter < 3){
//        servoModule->servoAngle(7,-60);
//        sleep(1);
//        servoModule->servoAngle(7,0);
//        sleep(1);
//        servoModule->servoAngle(7,60);
//        sleep(1);
//        servoModule->servoAngle(7,0);
//        sleep(1);
//        counter++;
//    }
    
//    Motors *motorModule = new Motors();
//    
//    motorModule->resetAddress();
//    motorModule->mbSetup(51.45);
//    motorModule->mbPWM(75);
//    motorModule->mbControl(motorModule->clockwise);
//    
//    sleep(15);
//    
//    motorModule->mbSpeed(200);
//    sleep(15);
//    motorModule->mbControl(motorModule->stop);
    
    i2c_end();

    

    return 0;
}

void lineModuleTest(){
    float lineSensors,prevLineSensors,currentError,prevError = 0,
            maxPWM = 60,minPWM = 0, maPWM = 15, mbPWM = 15, // - Default 25% PWM
            kp = 1,ki = 0.001,kd = 1,
            powerDifference = 0,sampleTime = 1/1000.0; // - 10[ms]
//    uint16_t sampleTime = 10;// - [ms]
    
    uint8_t inputs;    
    
//    LineFinder *lineFinder = new LineFinder(90,20,100);
//    lineFinder->setSpeed(50); // - 250[mm/s]

    Motors *motorModule = new Motors();
//    motorModule->selectModule();
//    motorModule->maSetup(51.45);
//    motorModule->mbSetup(51.45);
    motorModule->maPWM(0); // - Left Motor
    motorModule->mbPWM(0); // - Left Motor
    motorModule->maControl(motorModule->counter_clockwise); // - Left Motor
    motorModule->mbControl(motorModule->clockwise); // - Right Motor
    
    LineSensorModule *lineModule = new LineSensorModule();
    lineModule->initialize();
    
    uint16_t i = 0;
    sleep(2);
    while(i<5000){
        lineModule->selectModule();
        lineSensors = lineModule->readLine();
        if(lineSensors == 0){
            lineSensors = prevLineSensors*1.25;
        }
//        printf("Inputs: 0x%02X\n",inputs);
//        lineFinder->curveMeasurements(inputs);
//        leftSpeed = lineFinder->leftRPMSpeed();
//        printf("Left Speed: %d, ",leftSpeed);
//        rightSpeed = lineFinder->rightRPMSpeed();
//        printf("Right Speed: %d\n",rightSpeed);
        currentError = (350 - lineSensors)/350.0;
        prevLineSensors = lineSensors;
//        printf("%0.2f",lineSensors);
        // - Girar a la izquierda
        powerDifference += currentError*kp + (sampleTime*(prevError+currentError)/2.0)*ki + 
                ((currentError-prevError)/(2.0*sampleTime))*kd;
        prevError = currentError;
        
//        printf("PowerDifference: %0.5f\n",powerDifference);
        
//        if(powerDifference > maxPWM){
//            powerDifference = maxPWM;
//        }
//        if(powerDifference < -maxPWM){
//            powerDifference = -maxPWM;
//        }
//        powerDifference *= powerDifference;
        if(powerDifference == 0){ // - Centrado
            maPWM += 1;
            mbPWM += 1;
        }else{
//            printf("HERE\n");
//            return;
            maPWM *= 0.9;
            mbPWM *= 0.9;
            if(powerDifference < 0.0){ // - Girar a la derecha
                maPWM += -(powerDifference/2.0); // - Increase power
                mbPWM += (powerDifference/2.0); // - Decrease power
//                mbPWM += -powerDifference;
            }

            if(powerDifference > 0.0){ // - Girar Izquierda
                maPWM += -(powerDifference/2.0); // - Decrease Power
                mbPWM += (powerDifference/2.0); // - Increase Power
            }
        }
        
        maPWM = maxMinPWM(maPWM,maxPWM,minPWM);
        mbPWM = maxMinPWM(mbPWM,maxPWM,minPWM);     
//        printf("PowerDifference: %0.5f, maPWM: %0.2f, mbPWM: %0.2f\n",powerDifference,maPWM,mbPWM);
        motorModule->selectModule();
        motorModule->motorsPWM(maPWM,mbPWM);
        // - 50[ms] de muestreo
        usleep(1000);
        i++;
    }
    motorModule->selectModule();
    motorModule->maControl(motorModule->stop);
    motorModule->mbControl(motorModule->stop);
}

float maxMinPWM(float currentPWM, float maxPWM,float minPWM){
    if(currentPWM > maxPWM){
        return maxPWM;
    }

    if(currentPWM < minPWM){
        return minPWM;
    }
    
    return currentPWM;
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