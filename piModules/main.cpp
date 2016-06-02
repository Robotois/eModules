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
#include <cmath>
#include <chrono>
#include "Kalman.h"
//#include "LineFinder.h"
#include "AccelGyroModule.h"
#include "Robert.h"
#include "Robotina.h"

#include "Libraries/ADS1015/ADS1015.h"
#include "Libraries/PCA9685/PCA9685.h"
#include "Libraries/Timer/AccurateTiming.h"
#include "Modules/AnalogModules/OpticalDistanceSensor.h"
#include "Modules/AnalogModules/LightSensor.h"
#include "Modules/AnalogModules/TemperatureSensor.h"
#include "Modules/AnalogModules/RotaryModule.h"
#include "Modules/RGBLEDs/RGBLEDs.h"
#include "Modules/LCD/LCDModule.h"
#include "Modules/Ultrasonic/UltrasonicSensor.h"
#include "Modules/Servos/Servos.h"
#include "Modules/Motors/Motors.h"
#include "Modules/LineSensors/LineSensors.h"

#include <iostream>
#include <fstream>

//#include <armadillo>
#define RESTRICT_PITCH
using namespace std;
//using namespace arma;

void i2c_init();
void i2c_end();
//void uDelay(int delay_us);

void ServoTest();
void MotorModuleTest();
void LineSensorTest();
void LineFollower();
void robotinaTest();
void UltrasonicTest();

void AccelGyroTest();
void AccelGyroTest2();
int fullRange(uint16_t reading);
void armadilloTest();
void kalmanTest();
void kalmanTest2();
float getAngle(int meas, int zRef);
float axisAngle(int accMeas, int zRef);
void xAnglekalmanTest(float dt);
void yAnglekalmanTest(float dt);
void RobotRotationTest();
void RobertTest();
void MazeSolverTest();
float constrain(float value, float min, float max);

void DigitalSensorTest();
void SleepTest();

void LEDModuleTest();
void RGBTest();


/*
 * 
 */
int main(int argc, char** argv) {
    i2c_init();
    
//    AccelGyroModule * accelGyro = new AccelGyroModule();
//    accelGyro->calibrateMPU();
//    Robotina *robotina = new Robotina();
//    robotina->setup();
//    robotina->loop();
//    
    MotorModuleTest();
//    LineSensorTest();
////    LineFollower();
//
////    AccelGyroTest();
////    AccelGyroTest2();
////    armadilloTest();
//
////    kalmanTest2();
////    yAnglekalmanTest(0.020);
//    robotinaTest();
//    
//    UltrasonicTest();
//    ServoTest();
//    
////    RobotRotationTest();
////    MazeSolverTest();
////    SleepTest();
////    DigitalSensorTest();
    
//    LEDModuleTest();
//    RGBTest();
    
//    RotaryModule rotaty;
//    rotaty.selectPort(4);
//    printf("Light Input: %0.2f\n",rotaty.getValue());
//    printf("Raw Light Input: %d\n",rotaty.getScaledValue());

//    TemperatureSensor temp;
//    temp.selectPort(3);
//    printf("Temp Input: %0.2f\n",temp.getTemperature());
    
//    LightSensor lightSensor;
//    lightSensor.selectPort(2);
////    printf("Light Input: %0.2f\n",lightSensor.getLight());
//    printf("Raw Light Input: %d\n",lightSensor.getScaledLight());

//    ADS1015 *analog = new ADS1015;
//    analog->selectInput(ADS1015_SENSOR2,ADS1015_4096_GAIN);
//    float reading = analog->readInput();    
//    printf("Reading: %0.4f\n",reading);
//    
//    int16_t reading = analog->readRawInput();
//    printf("Raw Reading: %d\n",reading);

//    OpticalDistanceSensor distanceSensor;
//    distanceSensor.selectInputChannel(1);
//    printf("Distance: %0.4f\n",distanceSensor.getDistance());
//    uint8_t right_spaces;
//    LCDModule _lcd(0x01);
//    _lcd.initializeLCD();
////    _lcd.printChar('Y');
//    right_spaces = _lcd.message("Welcome to Robotois, the platform that\nallows you to create your own Robots");
//    printf("RightSpaces: %d\n",right_spaces);
//    _lcd.autoScroll(right_spaces);
//    _lcd.scrollDisplayLeft();
    i2c_end();    

    return 0;
}

void RGBTest(){
    RGBLEDs rgbs;
    rgbs.setRGB(1,128,0,128);
//    sleep(3);
    rgbs.setRGB(2,0,206,209);
//    sleep(3);
    rgbs.setRGB(3,128,128,0);
//    sleep(3);
//    rgbs.setRGB(1,0,0,0);
}

void LEDModuleTest(){
    uint8_t PIN = RPI_V2_GPIO_P1_32, PWM_CHANNEL  = 0;
    uint16_t RANGE = 1024;
    // Set the output pin to Alt Fun 5, to allow PWM channel 0 to be output there
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    uint16_t i = 0;
    while (1)
    {
        bcm2835_gpio_write(PIN, LOW);
        mDelay(250);
        bcm2835_gpio_write(PIN, HIGH);
        mDelay(250);
        i++;
        if(i>20)
            return;
    }    
}

void SleepTest(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int microseconds;
    uint8_t i = 0;
    while(i<50){
        startTime = std::chrono::high_resolution_clock::now();
//        usleep(20);
        usleep(200000);
        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();      
        printf("usleep: %d\n",microseconds);

        startTime = std::chrono::high_resolution_clock::now();
//        usleep(20);
        uDelay(200000);
        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();      
        printf("uDelay: %d\n",microseconds);
        i++;
    }
}

void DigitalSensorTest(){
    uint8_t sensorPin = RPI_V2_GPIO_P1_18;
    bcm2835_gpio_fsel(sensorPin,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(sensorPin, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_afen(sensorPin);   
    unsigned int i = 0;
    while(i<50){
        if(bcm2835_gpio_eds(sensorPin)){
            bcm2835_gpio_set_eds(sensorPin);
            cout << "Fall Event!!"<<endl;
        }
        usleep(250000);
        i++;
    }
    
}

void MazeSolverTest(){
    Robert *robert = new Robert();
    unsigned int i = 0;
    
    float kp = 2,ki = 0.001,kd = 15, currentError, prevError = 0, maxSpeed = 100, currentSpeed = 30,
            integral  = 0, speedDifference, distRef = 15;
    
    uint16_t maSpeed, mbSpeed;
    
    double distL,distR,distF;
    
    uint8_t digitalSensor = RPI_V2_GPIO_P1_18;

    bcm2835_gpio_fsel(digitalSensor,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(digitalSensor, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_len(digitalSensor); 
    bcm2835_gpio_set_eds(digitalSensor);
//    distL = leftDistance();
//    distR = rightDistance();
//    distF = frontDistance();
    
    robert->motorModule->selectModule();
    robert->motorModule->motorsPWM(0,0);
    robert->motorModule->motorsControl(Motors::counter_clockwise,Motors::clockwise); // - Left, Right
    
    robert->lookLeft();
    sleep(2);
    while(i <= 50){
        distL = robert->ultrasonicSensor->getDistance();

        // - Move Left
        if(distL >= 30){
            robert->moveForward(maxSpeed,maxSpeed);
            uDelay(550000);
            robert->stop();
            robert->turnLeft();
            robert->moveForward(maxSpeed,maxSpeed);
            uDelay(250000);
            distL = robert->ultrasonicSensor->getDistance();
            bcm2835_gpio_set_eds(digitalSensor);
        }

        // - Wall on front
        if(bcm2835_gpio_eds(digitalSensor)){
            robert->stop();
            
            robert->lookRight();
            distR = robert->ultrasonicSensor->getDistance();
            robert->lookLeft();
            
            if(distR >= 30){
//                robert->moveForward(maxSpeed,maxSpeed);
//                uDelay(50000);
//                robert->stop();
                robert->turnRight();
                robert->moveForward(maxSpeed,maxSpeed);
                uDelay(250000);
            }else{
                robert->turnAround();
                robert->moveForward(maxSpeed,maxSpeed);
                uDelay(200000);
            }
            
//            uDelay(50000);
            distL = robert->ultrasonicSensor->getDistance();
//            break;
            bcm2835_gpio_set_eds(digitalSensor);
        }
        
        currentError = distRef - distL;
        
        integral += currentError;
        speedDifference = kp* currentError + ki*integral + kd*(currentError - prevError);
        prevError = currentError;
        
        if(speedDifference < 0.0){
            maSpeed = maxSpeed + speedDifference;
            mbSpeed = maxSpeed;
        }else{
            maSpeed = maxSpeed;
            mbSpeed = maxSpeed - speedDifference;
        }
        
        robert->moveForward(maSpeed,mbSpeed);
        
//        // -- Follow Left Wall
//        distL = robert->leftDistance();
//        // - Left wall is close
//        if(distL <= 20 and distL > 15){
//            robert->moveForward(100,120); // * Move forward with left inclination
//        }
//        
//        // - Too close to left wall
//        if(distL <= 15){
//            robert->moveForward(120,100); // * Move forward with right inclination
//        }
        
//        if(currentSpeed < maxSpeed){
//            currentSpeed += 10;
//        }
        
//        uDelay(15000);

        i++;
    }
    robert->stop();
}

void RobertTest(){
    Robert *robertRobot = new Robert();
    
    robertRobot->turnLeft();
    sleep(1);
    robertRobot->turnRight();
    sleep(1);
    robertRobot->moveForward();
    sleep(1);
    robertRobot->moveBackward();
    sleep(1);
    robertRobot->stop();    
}

void RobotRotationTest(){
    Motors *motorModule = new Motors();
    motorModule->selectModule();
    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->counter_clockwise);
    motorModule->motorsSpeed(120,120);
    usleep(435000);
    motorModule->motorsControl(motorModule->stop,motorModule->stop);
}

void ServoTest(){
    Servos *servos = new Servos();
//    servos->initialize();
    while(1){
        servos->setAngle(0,-90);
        mDelay(5000);
        servos->setAngle(0,90);
        mDelay(5000);
    }
    
//    unsigned int i = 0;
//    float inc = +3;
//    float angle = 0;
//    while(i < 500){    
//        servos->setAngle(0,angle);
//        usleep(200000);
//        angle += inc;
//        if(angle >= 90.0){
//            inc = -3;
//        }
//        
//        if(angle <= -90){
//            inc = 3;
//        }
//        i++;
//    }
}

void UltrasonicTest(){
    float dist;
    UltrasonicSensor *ultrasonic = new UltrasonicSensor(2);
    dist = ultrasonic->getDistance();
    printf("Distance: %0.3f\n",dist);
}

void MotorModuleTest(){
    Motors *motorModule = new Motors();
//    motorModule->selectModule();
//    motorModule->motorsBasicTest();
    motorModule->motorsBasicSpeedTest();
//    motorModule->motorsSpeed(100,100);
//    mDelay(5000);
//    motorModule->motorsSetup25D();
//    motorModule->driveSpeeds(25,25);
//    mDelay(20);
//    motorModule->driveSpeeds(50,50);
//    mDelay(20);
//    motorModule->driveSpeeds(75,75);
//    mDelay(20);
//    motorModule->driveSpeeds(100,100);
//    mDelay(20);
//    motorModule->driveSpeeds(150,150);
//    mDelay(20);
//    motorModule->driveSpeeds(25,25);
//    mDelay(20);
//    motorModule->driveSpeeds(-25,-25);
//    mDelay(20);
//    motorModule->driveSpeeds(-50,-50);
//    mDelay(20);
//    motorModule->driveSpeeds(-75,-75);
//    mDelay(20);
//    motorModule->driveSpeeds(-100,-100);
//    mDelay(20);
//    motorModule->motorsControl(Motors::stop,Motors::stop);
    
//    motorModule->motorsControl(motorModule->counter_clockwise,motorModule->clockwise);
//    uint16_t rpms = 10;
//    for(int i = 0; i < 600 ; i++){
//        motorModule->motorsSpeed(rpms,rpms);
//        rpms += 5;
//        if(rpms > 400){
//            rpms = 10;
//        }
//        usleep(20000);
//    }
//    motorModule->motorsControl(motorModule->stop,motorModule->stop);
    
//    motorModule->motorsBasicTest();
//    motorModule->maBasicTest();
//    motorModule->maFullSpeedTest();
//    motorModule->maPIDResponse();

//    motorModule->mbBasicTest();
//    motorModule->mbFullSpeedTest();
//    motorModule->mbPIDResponse();
}

void LineSensorTest(){
    LineSensors *lineModule = new LineSensors();
//    lineModule->initialize();
    
    uint8_t inputs,singleInput;

    uint16_t i = 0;
    
    lineModule->setBackground(LINESENSORS_WHITE_BACKGROUND);
    while(i<7500){
//        lineModule->selectModule();
        inputs = lineModule->readSensors();
        singleInput = lineModule->readSensor(LINESENSORS_SENSOR1);
        printf("Sensors: 0x%02X \tSingle Sensor: %d\n",inputs,singleInput);
        usleep(500000);
    }
}

void LineFollower(){
    float lineReading,prevLineSensors,currentError,prevError = 0,
            maxPWM = 50,currentPWM = 15, maPWM, mbPWM, // - Default 25% PWM
            kp = 1,ki = 0.001,kd = 7,integral = 0,
            powerDifference = 0; // - 10[ms]
        
    Motors *motorModule = new Motors();
    motorModule->maPWM(0); // - Left Motor
    motorModule->mbPWM(0); // - Left Motor
    motorModule->maControl(motorModule->counter_clockwise); // - Left Motor
    motorModule->mbControl(motorModule->clockwise); // - Right Motor
    
    LineSensors *lineModule = new LineSensors();
//    lineModule->initialize();
    
    uint16_t i = 0;
    maPWM = currentPWM;
    mbPWM = currentPWM;
    sleep(2);
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
        usleep(10000);
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

void kalmanTest2(){
    float dt = 0.010,timer, integral = 0;
    string fileName = "yAngleResults.csv";
    
    Kalman kalmanX; // Create the Kalman instances
    Kalman kalmanY;

    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        
    // - CSV Dataset
    float pos,poshat,posmeas, vel, velhat;
    // - Archivo CSV con los resultados del filtro.
    ofstream outputFile(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    
    outputFile<<"\"time\",\"measured_angle\",\"estimated_angle\",\"estimated_drift\""<<endl;
    
    AccelGyroModule *accelGyro = new AccelGyroModule();
    accelGyro->initialize();
    accelGyro->selectModule();
    accelGyro->getMeas();

    kalmanX.setAngle(accelGyro->getXAngle()); // Set starting angle
    kalmanY.setAngle(accelGyro->getYAngle());

    uint16_t t = 0;
    uDelay((unsigned int)(1000*dt)*1000);
    while(t < 1000){
        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();      
        timer = (double)(microseconds) / 1000000; // Calculate delta time
//        printf("dt: %0.5f\n",timer);
        startTime = std::chrono::high_resolution_clock::now();
        
//        accelGyro->getAccelMeas();
//        accelGyro->getGyroMeas();
        accelGyro->getMeas();
        posmeas = accelGyro->getYAngle();
        poshat = kalmanY.getAngle(posmeas,accelGyro->getXGyro(),timer);
//        u = accelGyro->getXW();
//        // - Use a constant commanded acceleration of 1 foot/sec^2.
//        u = 1;
//        // - Simulate the linear system.
//        randValue1 = (rand() % 10000)*randStep - 1;
//        randValue2 = (rand() % 10000)*randStep - 1;
//        processNoise = accelnoise*((fvec){(dt*dt/2)*randValue1,dt*randValue2});
//        x = A * x + B * u + processNoise;
//        // - Simulate the noisy measurement
//        randValue1 = (rand() % 10000)*randStep - 1;
//        mNoise = measnoise * randValue1;
//        y = C * x + mNoise;
        // - Extrapolate the most recent state estimate to the present time.
//        x_hat = A * x_hat + B * u;
//        if(x_hat(0) > 360){
////            cout<<"Here1!!"<<endl;
//            x_hat(0) = (float)x_hat(0) -360;
//        }
//        if(x_hat(0) < 0){
////            cout<<"Here2!!"<<endl;
//            x_hat(0) = 360-(float)x_hat(0);
//        }
        // - Form the Innovation vector.
//        Inn = y - C * x_hat;
        // - Compute the covariance of the Innovation.
//        cout<<"Here3!!"<<endl;
//        s = C * P * C.t() + Sz;
        // - Form the Kalman Gain matrix.
//        K = A * P * C.t() * s.i();
        // - Update the state estimate.
//        x_hat = x_hat + K * Inn;
        // - Compute the covariance of the estimation error.
//        P = A * P * A.t() - A * P * C.t() * s.i() * C * P * A.t() + Sw;
        
//        cout<<"Here!!"<<endl;
//        pos = x(0);
//        posmeas = y(0);
//        poshat = x_hat(0);
//        vel = x(1);
//        velhat = x_hat(1);        
        outputFile<<t<<','<<posmeas<<','<<poshat<<','<<velhat<<','<<endl;  
        integral += poshat;
        uDelay((unsigned int)(1000*dt)*1000);
        t++;
    }
    printf("Average Offset: %0.5f \n",integral / 1000);
    outputFile.close();
}

void robotinaTest(){
    uint8_t stopButton = RPI_V2_GPIO_P1_11;

    bcm2835_gpio_fsel(stopButton,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(stopButton, BCM2835_GPIO_PUD_DOWN);
    bcm2835_gpio_hen(stopButton);
//    bcm2835_gpio_set_eds(stopButton);
    
    // - Plotting variables
    string fileName;
    // - CSV Dataset
//    float angle;
    // - Archivo CSV con los resultados.
    ofstream outputFile;    
    // - Plotting DataSet
    fileName = "yAngleResults.csv";
    outputFile.open(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    outputFile<<"\"time\",\"angle\",\"control\",\"mean_error\""<<endl;    
    
//    float filtered_angle = 0, sample = 0, last_sample = 0;   
//    float angle_integral = 0;
    float dt = 0.005f;
    float targetAngle = 0.5f,currentAngleMeas,currentGyroMeas,currentAngle, 
            currentError,prevError = 0.0f,
            controlSignal,maPWM, mbPWM,maSpeed, mbSpeed, ControlPWMRatio = 10,
        kp = 5.0f,ki = 0.001f,kd = 30.0f,integral = 0.0f,
        kp_fb,ki_fb,kd_fb;

    unsigned long int timerCount;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        
    Motors *motorModule = new Motors();
    motorModule->selectModule();
    motorModule->motorsSetup25D();
//    motorModule->motorsPWM(0,0); // - Left Motor

    
//    Kalman kalmanX; // Create the Kalman instances
    Kalman kalmanY;
    AccelGyroModule *accelGyro = new AccelGyroModule();
    if(accelGyro->testConnection()){
        printf("AccelGyro Module connection successful...\n");
    }else{
        printf("AccelGyro Module connection failed!!!\n");
        return;
    }
    accelGyro->initialize();
    accelGyro->selectModule();
    accelGyro->getMeas();

    // - Get Starting angle
//    kalmanX.setAngle(accelGyro->getXAngle()); // Set starting angle
//    kalmanY.setAngle(accelGyro->getYAngle());
//    angle_integral = accelGyro->getRoll();
    currentAngleMeas = accelGyro->getRoll();
//    integral += currentAngleMeas / 200;
    kalmanY.setAngle(currentAngleMeas);
//    accelGyro->kalman_yInit(dt+0.002);

    
    uint16_t t = 0;
    unsigned int dt_us = (1000000*dt);
    mDelay(2);
    auto loopTimer = std::chrono::high_resolution_clock::now();    
    while(1){
        if(bcm2835_gpio_eds(stopButton)){
            bcm2835_gpio_set_eds(stopButton);
            motorModule->motorsControl(Motors::stop,Motors::stop);
            printf("Bye Bye...\n");
            return;
        }
        
//        elapsedTime = std::chrono::high_resolution_clock::now() - loopTimer;
//        timerCount = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();      
//        dt = (float)(timerCount) / 1000.0f; // Calculate delta time
//        printf("dt: %0.5f\n",timer);
//        loopTimer = std::chrono::high_resolution_clock::now();
        
//        accelGyro->getAccelMeas();
//        accelGyro->getGyroMeas();
        accelGyro->selectModule();
        accelGyro->getMeas();
        currentAngleMeas = accelGyro->getRoll();
        currentGyroMeas = accelGyro->getXGyro();
        currentAngle = kalmanY.getAngle(currentAngleMeas,currentGyroMeas,dt);
//        angle_integral += currentAngle;

//        sample = currentAngle;
//        filtered_angle = 0.996 * (filtered_angle + sample - last_sample);
//        last_sample = sample;
        
//        accelGyro->selectModule();
//        currentAngle = accelGyro->kalman_yAngle();

        currentError = targetAngle - currentAngle;
        integral += currentError;
        integral = constrain(integral, -10.0f, 10.0f);

//        if(currentError < 0){
//            currentError *= 1.75;
//        }else{
//            currentError *= 0.75;
//        }
        
//        if(currentError < 0){
//            currentError = - currentError*currentError;
//        }else{
//            currentError = currentError*currentError;
//        }
        
        motorModule->selectModule();
        if(abs(currentAngle) >= 45.0){
            motorModule->motorsControl(Motors::stop,Motors::stop);
            accelGyro->outputFile.close();
            cout << "I'm Falling!!!"<< '\n';    
            return;
        }
        
        // - PID Control
        kp_fb = currentError*kp;
        ki_fb = integral*ki;
        kd_fb = (currentError - prevError)*kd;
        controlSignal = kp_fb + ki_fb + kd_fb;
        prevError = currentError;
//        printf("CurrentAngle: %0.5f; ControlSignal: %0.5f\n",currentAngle,controlSignal);        
        
//        if(controlSignal >= 0.0){ // - Move Forward
////            motorModule->motorsControl(Motors::clockwise,Motors::counter_clockwise);
//
////            maPWM = controlSignal;
////            mbPWM = controlSignal;
//            maSpeed= controlSignal;
//            mbSpeed = controlSignal;
//        }else{ // - Move Backward
//            motorModule->motorsControl(Motors::counter_clockwise,Motors::clockwise);
//
////            maPWM = -controlSignal;
////            mbPWM = -controlSignal;
//
//            maSpeed= -controlSignal;
//            mbSpeed= -controlSignal;
//        }
        
//        if(maPWM > 100.0){
//           maPWM = 100.0; 
//        }
//        if(mbPWM > 100.0){
//           mbPWM = 100.0; 
//        }
//        if(maSpeed > 300.0){
//           maSpeed = 300.0; 
//        }
//        if(mbSpeed > 300.0){
//           mbSpeed = 300.0; 
//        }
        controlSignal *= ControlPWMRatio;
        motorModule->drivePWMs((int)controlSignal,(int)controlSignal);
//        motorModule->driveSpeeds((int)controlSignal,(int)controlSignal);
        
//        outputFile<<t<<','<<currentAngle<<','<<controlSignal<<','<<angle_integral/t<<endl;            
        elapsedTime = std::chrono::high_resolution_clock::now() - loopTimer;  
        timerCount = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
        while (timerCount < dt_us){
            elapsedTime = std::chrono::high_resolution_clock::now() - loopTimer;  
            timerCount = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
        }
        loopTimer = std::chrono::high_resolution_clock::now();            
//        uDelay(dtus);
//        t++;
    }
    motorModule->selectModule();
    motorModule->motorsControl(Motors::stop,Motors::stop);
    motorModule->motorsPWM(0,0);
//    motorModule->mbControl(motorModule->stop);
    outputFile.close();
}

float constrain(float value, float min, float max){
    if(value < min)
        return min;
    if(value > max)
        return max;
    
    return value;
}
//void xAnglekalmanTest(float dt){ // - dt en s
//    string fileName = "xAngleResults.csv";
//    float measnoise = 5.0, accelNoise = 0.5,driftNoise = 0.5,u;
//    fmat A = {{1.0,-dt},{0.0,1.0}},s,K;
//    fvec B = {dt, 0};
//    frowvec C = {1.0,0.0};
//    fvec x = {0.0,0.0},y = {0},Inn;
//    fvec x_hat(x);
//    
//    float Sz = measnoise*measnoise;
//    fmat Sw = {{dt*accelNoise*accelNoise, 0},{0, dt*driftNoise*driftNoise}};
//    fmat P(Sw);
//    
//    // - CSV Dataset
//    float pos,poshat,posmeas, vel, velhat;
//    // - Archivo CSV con los resultados del filtro.
//    ofstream outputFile(fileName.c_str(),ios_base::out);
//    if ( ! outputFile.is_open() ){    
//        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
//        exit(1);
//    }
//    
//    outputFile<<"\"time\",\"measured_angle\",\"estimated_angle\",\"estimated_drift\""<<endl;
//    
//    AccelGyroModule *accelGyro = new AccelGyroModule();
//    accelGyro->initialize();
//    accelGyro->selectModule();
//    
//    uint16_t t = 0;
//    while(t < 2500){
//        accelGyro->getAccelMeas();
//        accelGyro->getGyroMeas();
//        y(0) = accelGyro->getXAngle();
//        u = - accelGyro->getYW();
////        // - Use a constant commanded acceleration of 1 foot/sec^2.
////        u = 1;
////        // - Simulate the linear system.
////        randValue1 = (rand() % 10000)*randStep - 1;
////        randValue2 = (rand() % 10000)*randStep - 1;
////        processNoise = accelnoise*((fvec){(dt*dt/2)*randValue1,dt*randValue2});
////        x = A * x + B * u + processNoise;
////        // - Simulate the noisy measurement
////        randValue1 = (rand() % 10000)*randStep - 1;
////        mNoise = measnoise * randValue1;
////        y = C * x + mNoise;
//        // - Extrapolate the most recent state estimate to the present time.
//        x_hat = A * x_hat + B * u;
////        if(x_hat(0) > 360){
//////            cout<<"Here1!!"<<endl;
////            x_hat(0) = (float)x_hat(0) -360;
////        }
////        if(x_hat(0) < 0){
//////            cout<<"Here2!!"<<endl;
////            x_hat(0) = 360-(float)x_hat(0);
////        }
//        // - Form the Innovation vector.
//        Inn = y - C * x_hat;
//        // - Compute the covariance of the Innovation.
////        cout<<"Here3!!"<<endl;
//        s = C * P * C.t() + Sz;
//        // - Form the Kalman Gain matrix.
//        K = A * P * C.t() * s.i();
//        // - Update the state estimate.
//        x_hat = x_hat + K * Inn;
//        // - Compute the covariance of the estimation error.
//        P = A * P * A.t() - A * P * C.t() * s.i() * C * P * A.t() + Sw;
//        
////        cout<<"Here!!"<<endl;
//        pos = x(0);
//        posmeas = y(0);
//        poshat = x_hat(0);
//        vel = x(1);
//        velhat = x_hat(1);
//        outputFile<<t<<','<<posmeas<<','<<poshat<<','<<velhat<<endl;            
//        usleep((unsigned int)(1000*dt)*1000);
//        t++;
//    }
//    outputFile.close();
//    
//}
//
//void yAnglekalmanTest(float dt){ // - dt en s
//    string fileName = "yAngleResults.csv";
//    float measnoise = 0.003, accelNoise = 0.001,driftNoise = 0.003,u;
//    fmat A = {{1.0,-dt},{0.0,1.0}},s,K;
//    fvec B = {dt, 0};
//    frowvec C = {1.0,0.0};
//    fvec x = {0.0,0.0},y = {0},Inn;
//    fvec x_hat(x);
//    auto startTime = std::chrono::high_resolution_clock::now();
//    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
//    
//    float Sz = measnoise*measnoise;
//    fmat Sw = {{dt*accelNoise*accelNoise, 0},{0, dt*driftNoise*driftNoise}};
//    fmat P(Sw);
//    
//    // - CSV Dataset
//    float pos,poshat,posmeas, vel, velhat;
//    // - Archivo CSV con los resultados del filtro.
//    ofstream outputFile(fileName.c_str(),ios_base::out);
//    if ( ! outputFile.is_open() ){    
//        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
//        exit(1);
//    }
//    
//    outputFile<<"\"time\",\"measured_angle\",\"estimated_angle\",\"estimated_drift\""<<endl;
//    
//    AccelGyroModule *accelGyro = new AccelGyroModule();
//    accelGyro->initialize();
//    accelGyro->selectModule();
//    accelGyro->getMeas();
//    x_hat(0) = accelGyro->getYAngle();
//
//    uint16_t t = 0;
//    usleep((unsigned int)(1000*dt)*1000);
//    while(t < 1500){
////        accelGyro->getAccelMeas();
////        accelGyro->getGyroMeas();
//        accelGyro->getMeas();
//        y(0) = accelGyro->getYAngle();
//        u = accelGyro->getXW();
////        // - Use a constant commanded acceleration of 1 foot/sec^2.
////        u = 1;
////        // - Simulate the linear system.
////        randValue1 = (rand() % 10000)*randStep - 1;
////        randValue2 = (rand() % 10000)*randStep - 1;
////        processNoise = accelnoise*((fvec){(dt*dt/2)*randValue1,dt*randValue2});
////        x = A * x + B * u + processNoise;
////        // - Simulate the noisy measurement
////        randValue1 = (rand() % 10000)*randStep - 1;
////        mNoise = measnoise * randValue1;
////        y = C * x + mNoise;
//        // - Extrapolate the most recent state estimate to the present time.
//        x_hat = A * x_hat + B * u;
////        if(x_hat(0) > 360){
//////            cout<<"Here1!!"<<endl;
////            x_hat(0) = (float)x_hat(0) -360;
////        }
////        if(x_hat(0) < 0){
//////            cout<<"Here2!!"<<endl;
////            x_hat(0) = 360-(float)x_hat(0);
////        }
//        // - Form the Innovation vector.
//        Inn = y - C * x_hat;
//        // - Compute the covariance of the Innovation.
////        cout<<"Here3!!"<<endl;
//        s = C * P * C.t() + Sz;
//        // - Form the Kalman Gain matrix.
//        K = A * P * C.t() * s.i();
//        // - Update the state estimate.
//        x_hat = x_hat + K * Inn;
//        // - Compute the covariance of the estimation error.
//        P = A * P * A.t() - A * P * C.t() * s.i() * C * P * A.t() + Sw;
//        
////        cout<<"Here!!"<<endl;
//        pos = x(0);
//        posmeas = y(0);
//        poshat = x_hat(0);
//        vel = x(1);
//        velhat = x_hat(1);
//        outputFile<<t<<','<<posmeas<<','<<poshat<<','<<velhat<<endl;            
//        usleep((unsigned int)(1000*dt)*1000);
//        t++;
//        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
//        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();      
//        dt = (double)(microseconds) / 1000000; // Calculate delta time
//        printf("dt: %0.5f\n",dt);
//        startTime = std::chrono::high_resolution_clock::now();
//        
//    }
//    outputFile.close();
//    
//}
//
//void AccelGyroTest2(){
//    AccelGyroModule *accelGyro = new AccelGyroModule();
//    accelGyro->initialize();
//    accelGyro->selectModule();
//    accelGyro->getAccelMeas();
//    accelGyro->getGyroMeas();
//}
//
//void AccelGyroTest(){
//    /** Gyro Full-Scale Range
//     * FS_SEL=0 => ±250º/s
//     * FS_SEL=1 => ±500º/s
//     * FS_SEL=2 => ±1000º/s
//     * FS_SEL=3 => ±2000º/s
//     * 
//     * Accel Full-Scale Range
//     * AFS_SEL=0 => ±2 g
//     * AFS_SEL=1 => ±4 g
//     * AFS_SEL=2 => ±8 g
//     * AFS_SEL=3 => ±16 g
//     */
//    uint8_t GYRO_FS_SEL = 0,ACCEL_FS_SEL = 0;
//    static const float gyroScaleFactors[] = {131,65.5,32.8,16.4},
//            accelScaleFactors[] = {16384,8192,4096,2048};
//    // - Registers
//    static const uint8_t PWR_MGMT_1 = 0x6B,CONFIG = 0x1A,
//            GYRO_CONFIG = 0x1B, ACCEL_CONFIG = 0x1C,
//            ACCEL_XOUT_H = 0x3B, ACCEL_XOUT_L = 0x3C, ACCEL_YOUT_H = 0x3D, 
//            ACCEL_YOUT_L = 0x3E, ACCEL_ZOUT_H = 0x3F, ACCEL_ZOUT_L = 0x40,
//            GYRO_XOUT_H = 0x43, GYRO_XOUT_L = 0x44, GYRO_YOUT_H = 0x45, 
//            GYRO_YOUT_L = 0x46, GYRO_ZOUT_H = 0x47, GYRO_ZOUT_L = 0x48;
//    
//    uint8_t result;
//    
//    // - MPU6050_init
//    char rBuf[10]; // - Max length
//    char wBuf[10]; // - Max length
//    
//    bcm2835_i2c_setSlaveAddress(0x69);
//    
//    // - Clear sleep bit
//    wBuf[0] = PWR_MGMT_1;
//    wBuf[1] = 0x00;
//    result = bcm2835_i2c_write(wBuf, 2);
//    printf("PWR Config Result: %d\n",result);
//    
//    wBuf[0] = CONFIG;
//    wBuf[1] = 0x00;
//    result = bcm2835_i2c_write(wBuf, 2);
//    printf("Config Result: %d\n",result);
//    
//    // - Burst Write Sequence
////    GYRO_FS_SEL = 0;
//    wBuf[0] = GYRO_CONFIG; // - Gyro and Accel config registers have consecutive addresses
//    wBuf[1] = GYRO_FS_SEL;
//    wBuf[2] = ACCEL_FS_SEL;
//    result = bcm2835_i2c_write(wBuf, 3);
//    printf("AccelGyro Config Result: %d\n",result);
//    
//    // - Accel measurements (Burst Read Sequence)
//    int accelXOut, accelYOut,accelZOut;
//    float scaleFactor = accelScaleFactors[ACCEL_FS_SEL];
//    double accelX, accelY, accelZ, roll, pitch;
//    wBuf[0] = ACCEL_XOUT_H; // - Initial register address
//    bcm2835_i2c_write(wBuf, 1);
//    result = bcm2835_i2c_read(rBuf, 6); // - 
//    printf("Accel Measurement Status: %d\n",result);
//    
//    accelXOut = fullRange((rBuf[0] << 8) | rBuf[1]);
//    accelYOut = fullRange((rBuf[2] << 8) | rBuf[3]);
//    accelZOut = fullRange((rBuf[4] << 8) | rBuf[5]);
//    
//    accelX = accelXOut/scaleFactor;
//    accelY = accelYOut/scaleFactor;
//    accelZ = accelZOut/scaleFactor;
//    
//    roll  = atan(accelY/accelZ) *180/M_PI;
//    pitch = atan(-accelX/ sqrt(accelY*accelY + accelZ*accelZ) )*180/M_PI;
//    
////    printf("- AccelX = %d; Scaled: %0.5f => xAngle: %0.5f\n",accelXOut,accelX,axisAngle(accelXOut,accelZOut));
////    printf("- AccelY = %d; Scaled: %0.5f => yAngle: %0.5f\n",accelYOut,accelY,axisAngle(accelYOut,accelZOut));
//    printf("- AccelX = %d; Scaled: %0.5f => Pitch: %0.5f\n",accelXOut,accelX,pitch);
//    printf("- AccelY = %d; Scaled: %0.5f => Roll: %0.5f\n",accelYOut,accelY,roll);
//    printf("- AccelZ = %d; Scaled: %0.5f\n",accelZOut,accelZ);
//    
//    // - Gyro measurements (Burst Read Sequence)
//    int gyroXOut, gyroYOut,gyroZOut;
//    scaleFactor = gyroScaleFactors[GYRO_FS_SEL];
//    wBuf[0] = GYRO_XOUT_H; // - Initial register address
//    bcm2835_i2c_write(wBuf, 1);
//    result = bcm2835_i2c_read(rBuf, 6); // - 
//    printf("Gyro Measurement Status: %d\n",result);
//    
//    gyroXOut = fullRange((rBuf[0] << 8) | rBuf[1]);
//    gyroYOut = fullRange((rBuf[2] << 8) | rBuf[3]);
//    gyroZOut = fullRange((rBuf[4] << 8) | rBuf[5]);
//    printf("- GyroX = %d; Scaled: %0.5f\n",gyroXOut,gyroXOut/scaleFactor);
//    printf("- GyroY = %d; Scaled: %0.5f\n",gyroYOut,gyroYOut/scaleFactor);
//    printf("- GyroZ = %d; Scaled: %0.5f\n",gyroZOut,gyroZOut/scaleFactor);
//}
//
///**
// * Obtains the angle of the given axis measurement considering the z-axis measurement as
// * reference.
// * @param meas
// * @param zRef
// * @return 
// */
//float getAngle(int meas, int zRef){
//    // - Cuadrant I and IV
//    if(zRef >= 0){
//        return atan((float)meas/zRef) * 180/M_PI;
//    }else{    // - Cuadrant II and III
//        // - II
//        if(meas >= 0){
//            return 180 + atan((float)meas/zRef)* 180/M_PI;
//        }else{ // - III
//            return -180 + atan((float)meas/zRef)* 180/M_PI;
//        }
//    }    
//}
//
///**
// * Obtains the angle of the given axis measurement considering the z-axis measurement as
// * reference.
// * @param meas
// * @param zRef
// * @return 
// */
//float axisAngle(int accMeas, int zRef){
//    // - Angle on x Axis changing positively => CounterClockWise
//    // - Cuadrant I and IV
//    if(zRef >= 0){
//        if(accMeas >= 0) // - Cuadrant I
//            return atan((float)accMeas/zRef);
//        else // - Cuadrant IV, tan^{-1} returns negative angle
//            return 2*M_PI + atan((float)accMeas/zRef);
//    }else{    // - Cuadrant II and III
//        return M_PI + atan((float)accMeas/zRef);
//    }    
//}
//
//int fullRange(uint16_t reading){
//    if(reading >= 0x8000)
//        return -((65535 - reading)+1);
//    else
//        return (int)reading;
//}
//
//// -- Manejo de matrices
//void armadilloTest(){
//    mat A = randu<mat>(4,5);
//    mat B = randu<mat>(4,5);
//  
//    cout << A*B.t() << endl;  
//}
//
//void kalmanTest(uint16_t duration, float dt){
//    string fileName = "kalmanResults.csv";
//    float measnoise = 10.0, accelnoise = 0.2;
//    fmat A = {{1.0,dt},{0.0,1.0}},s,K;
//    fvec B = {dt*dt/2, dt};
//    frowvec C = {1.0,0.0};
//    fvec x = {0.0,0.0},y,Inn;
//    fvec x_hat(x);
//    
//    float Sz = measnoise*measnoise;
//    fmat Sw = (accelnoise*accelnoise)*((fmat){{dt*dt*dt*dt/4, dt*dt*dt/2},{dt*dt*dt/2, dt*dt}});
////    Sw *= ;
//    fmat P(Sw);
//    
//    // - Plotting Data
//    float pos,poshat,posmeas, vel, velhat;
//    
//    // - Archivo CSV con los resultados del filtro.
//    ofstream outputFile(fileName.c_str(),ios_base::out);
//    if ( ! outputFile.is_open() ){    
//        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
//        exit(1);
//    }
//    
//    outputFile<<"\"time\",\"true_position\",\"measured_position\",\"estimated_position\",\"true_velocity\",\"estimated_velocity\""<<endl;
//    
//    float t = 0.0, u,mNoise;
//    fvec processNoise;
//
//    // - Numeros aleatorios
//    srand (time(NULL));
//    
//    float randStep = 2.0/10000; //Pasos discretos
//    float randValue1,randValue2;
//    
//    while(t < duration){
//        // - Use a constant commanded acceleration of 1 foot/sec^2.
//        u = 1;
//        // - Simulate the linear system.
//        randValue1 = (rand() % 10000)*randStep - 1;
//        randValue2 = (rand() % 10000)*randStep - 1;
//        processNoise = accelnoise*((fvec){(dt*dt/2)*randValue1,dt*randValue2});
//        x = A * x + B * u + processNoise;
//        // - Simulate the noisy measurement
//        randValue1 = (rand() % 10000)*randStep - 1;
//        mNoise = measnoise * randValue1;
//        y = C * x + mNoise;
//        // - Extrapolate the most recent state estimate to the present time.
//        x_hat = A * x_hat + B * u;
//        // - Form the Innovation vector.
//        Inn = y - C * x_hat;
//        // - Compute the covariance of the Innovation.
//        s = C * P * C.t() + Sz;
//        // - Form the Kalman Gain matrix.
//        K = A * P * C.t() * s.i();
//        // - Update the state estimate.
//        x_hat = x_hat + K * Inn;
//        // - Compute the covariance of the estimation error.
//        P = A * P * A.t() - A * P * C.t() * s.i() * C * P * A.t() + Sw;
//        
////        cout<<"Here!!"<<endl;
//        pos = x(0);
//        posmeas = y(0);
//        poshat = x_hat(0);
//        vel = x(1);
//        velhat = x_hat(1);
//        outputFile<<t<<','<<pos<<','<<posmeas<<','<<poshat<<','<<vel<<','<<velhat<<endl;            
//        t += dt;
//    }
//    outputFile.close();
//    
//}

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

////*****************************************************
////*****************************************************
////********** DELAY FOR # uS WITHOUT SLEEPING **********
////*****************************************************
////*****************************************************
////Using delayMicroseconds lets the linux scheduler decide to jump to another process.  Using this function avoids letting the
////scheduler know we are pausing and provides much faster operation if you are needing to use lots of delays.
//void uDelay(int delay_us){
//    long int start_time;
//    long int time_difference;
//    struct timespec gettime_now;
//
//    clock_gettime(CLOCK_REALTIME, &gettime_now);
//    start_time = gettime_now.tv_nsec;		//Get nS value
//    while (1)
//    {
//        clock_gettime(CLOCK_REALTIME, &gettime_now);
//        time_difference = gettime_now.tv_nsec - start_time;
//        if (time_difference < 0)
//            time_difference += 1000000000;				//(Rolls over every 1 second)
//        if (time_difference > (delay_us * 1000))		//Delay for # nS
//            break;
//    }
//
//}