/* 
 * File:   Robert.cpp
 * Author: yova
 * 
 * Created on 19 de abril de 2016, 01:21 PM
 */

#include <stdint.h>

#include "Robert.h"
#include "../../Libraries/Timer/AccurateTiming.h"

Robert::Robert() {
    lineModule = new LineSensors();
    motorModule = new Motors();
//    ultrasonicSensor = new UltrasonicSensor(0x02);
//    servos = new Servos();
//    servos->initialize();
}

Robert::Robert(const Robert& orig) {
}

Robert::~Robert() {
}

void Robert::LineFollower(){
    float lineReading,prevLineSensors,currentError,prevError = 0,
            maxPWM = 60,currentPWM = 20, maPWM, mbPWM, // - Default 25% PWM
            kp = 1,ki = 0.001,kd = 7,integral = 0,
            powerDifference = 0; // - 10[ms]
        
//    motorModule->maPWM(0); // - Left Motor
//    motorModule->mbPWM(0); // - Left Motor
//    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->clockwise); // - Left, Right
//    motorModule->mbControl(); // - Right Motor
    
//    lineModule->initialize();
    
    uint16_t i = 0;
    maPWM = currentPWM;
    mbPWM = currentPWM;
    mDelay(2000);
    while(i<2500){
//        lineModule->selectModule();
        lineReading = lineModule->readLine();
        if(lineReading == -1.0){
            lineReading = prevLineSensors;
        }
//        printf("Inputs: 0x%02X\n",inputs);
//        lineFinder->curveMeasurements(inputs);
//        leftSpeed = lineFinder->leftRPMSpeed();
//        printf("Left Speed: %d, ",leftSpeed);
//        rightSpeed = lineFinder->rightRPMSpeed();
//        printf("Right Speed: %d\n",rightSpeed);
        currentError = lineReading - 250;
        prevLineSensors = lineReading;
//        printf("%0.2f",lineSensors);

        // - PID Control
        integral += currentError;
        powerDifference = currentError*kp + integral*ki + (currentError-prevError)*kd;
        prevError = currentError;
        
//        printf("PowerDifference: %0.5f\n",powerDifference);
        
//        if(powerDifference > currentPWM){
//            powerDifference = currentPWM;
//        }
//        if(powerDifference < -currentPWM){
//            powerDifference = -currentPWM;
//        }
        constrain(&powerDifference,-currentPWM,currentPWM);
        if(powerDifference < 0.0){ // - Girar a la izquierda
            maPWM = currentPWM + powerDifference; // - Decrease power
            mbPWM = currentPWM;
        }else{
            maPWM = currentPWM;
            mbPWM = currentPWM - powerDifference; // - Decrease Power
        }
//        printf("PowerDifference: %0.5f, maPWM: %0.2f, mbPWM: %0.2f\n",powerDifference,maPWM,mbPWM);
//        motorModule->selectModule();
        motorModule->drivePWMs((int16_t)(maPWM*10),(int16_t)(mbPWM*10));
        // - 1[ms] de muestreo
        uDelay(10000);
        i++;
        // - Slow init speed, gradually increase it to the maximum value
        if(currentPWM < maxPWM){
            currentPWM += 0.1;
        }
    }
//    motorModule->selectModule();
    motorModule->motorsControl(motorModule->stop,motorModule->stop); // - Left, Right
}

void Robert::MazeSolver(){
    uint16_t i = 0;
    while(i < 5){
        estimateDirection();
        moveForward();
        uDelay(500000);
        stop();
        i++;
    }
}

void Robert::estimateDirection(){
    double distL,distR,distF;

    while(true){
        distL = leftDistance();
        distR = rightDistance();
        distF = frontDistance();

        if(distL <= 15 and distR <= 15 and distF <= 7.5){
            turnAround();
            break;
        }

        if(distL > 15){
            turnLeft();
            break;
        }

        if(distF > 7.5){
            break;
        }
        
        if(distR > 15){
            turnRight();
            break;
        }
    }
//    moveForward();
}

void Robert::turnAround(){
    motorModule->selectModule();
//    moveBackward();
//    uDelay(150000);
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->counter_clockwise);
    motorModule->motorsSpeed(120,120);
    uDelay(850000);
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
}

void Robert::turnRight(){
    motorModule->selectModule();
//    moveBackward();
//    uDelay(150000);
    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->counter_clockwise);
    motorModule->motorsSpeed(120,120);
    uDelay(450000);
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
}

void Robert::turnLeft(){
    motorModule->selectModule();
//    moveBackward();
//    uDelay(150000);
    motorModule->motorsControl(motorModule->clockwise,motorModule->clockwise);
    motorModule->motorsSpeed(120,120);
    uDelay(450000);
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
}

void Robert::moveForward(){
    motorModule->selectModule();
    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->clockwise);
    motorModule->motorsSpeed(150,150);
}

void Robert::moveForward(uint16_t maSpeed,uint16_t mbSpeed){
    motorModule->selectModule();
    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->clockwise);
    motorModule->motorsSpeed(maSpeed,mbSpeed);
}

void Robert::moveBackward(){
    motorModule->selectModule();
    motorModule->motorsControl(motorModule->clockwise,motorModule->counter_clockwise);
    motorModule->motorsSpeed(150,150);
}

void Robert::stop(){
    motorModule->selectModule();
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
    motorModule->motorsPWM(0,0);
}

double Robert::leftDistance(){
    lookLeft();
//    uDelay(300000);
    return ultrasonicSensor->getDistance();    
}

double Robert::rightDistance(){
    lookRight();
//    uDelay(500000);
    return ultrasonicSensor->getDistance();    
}

double Robert::frontDistance(){
//    servos->selectModule();
    servos->setAngle(0,0.0);
//    uDelay(500000);
    return ultrasonicSensor->getDistance();    
}

void Robert::lookLeft(){
//    servos->selectModule();
    servos->setAngle(0,+100);    
    uDelay(400000);
}

void Robert::lookRight(){
//    servos->selectModule();
    servos->setAngle(0,-100);    
    uDelay(400000);
}

void Robert::constrain(float* value, float min, float max){
    if(*value > max){
        *value = max;
        return;
    }
    
    if(*value < min){
        *value = min;
        return;
    }    
}