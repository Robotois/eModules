/* 
 * File:   Motors.cpp
 * Author: yova
 * 
 * Created on 26 de enero de 2016, 06:15 PM
 */

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <cmath>
#include "Motors.h"
#include "../../Libraries/Timer/AccurateTiming.h"
#include <bcm2835.h>


using namespace std;

Motors::Motors(uint8_t _add) {
    if(_add > 1){
        printf("Wrong slave address for the Digital IO Module...\n");
        return;
    }
    slave_address = 0x10 | _add; // - Direccion por default
    bcm_init();
    
    leftMotor = MOTORS_MOTOR2_CONN;
    rightMotor = MOTORS_MOTOR1_CONN;
    
    motorsControl(MOTORS_STOP,MOTORS_STOP);
}

Motors::Motors(const Motors& orig) {
}

Motors::~Motors() {
    bcm_end();
}

/**
 * Reestablece la direccion del esclavo en l puerto i2c. Se debe llamar antes de
 * iniciar una transaccion o serie de transacciones hacia el modulo de motores.
 */
void Motors::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_address);
}

/**
 * Establece el sentido de giro y permite detener el motor A.
 * @param control => 0 --> Stop, 1 --> counter_clockwise, 2 --> clockwise.
 */
void Motors::motor1Control(uint8_t control){
    selectModule();
    wBuf[0] = MOTORS_M1_CONTROL; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
}

/**
 * Establece el PWM del motor A.
 * @param pwm => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::motor1PWM(float pwm){
    selectModule();
    
    realMotor1PWM = constrainPWM(pwm);

    wBuf[0] = MOTORS_M1_PWM;
    wBuf[1] = (uint8_t)realMotor1PWM;
    wBuf[2] = (uint8_t)(realMotor1PWM >> 8);

    bcm2835_i2c_write(wBuf, 3);
}

/**
 * Establece el sentido de giro y permite detener el motor B.
 * @param control => 0 --> Stop, 1 --> counter_clockwise, 2 --> clockwise.
 */
void Motors::motor2Control(uint8_t control){
    selectModule();
    wBuf[0] = MOTORS_M2_CONTROL; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
}

/**
 * Establece el PWM del motor B.
 * @param pwm => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::motor2PWM(float pwm){
    selectModule();
    
    realMotor2PWM = constrainPWM(pwm);
    
    wBuf[0] = MOTORS_M2_PWM;
    wBuf[1] = (uint8_t)realMotor2PWM;
    wBuf[2] = (uint8_t)(realMotor2PWM >> 8);

    bcm2835_i2c_write(wBuf, 3);
}

void Motors::motorsControl(uint8_t m1Control, uint8_t m2Control){
    selectModule();
    wBuf[0] = MOTORS_M1_CONTROL; // - Direccion del registro
    wBuf[1] = m1Control; // - Contenido del registro
    wBuf[2] = m2Control; // - Contenido del registro
    bcm2835_i2c_write(wBuf,3);
}

void Motors::motorsPWM(float m1PWM, float m2PWM){
    selectModule();

    realMotor1PWM = constrainPWM(m1PWM);
    realMotor2PWM = constrainPWM(m2PWM);

    wBuf[0] = MOTORS_M1_PWM;
    wBuf[1] = (uint8_t)realMotor1PWM;
    wBuf[2] = (uint8_t)(realMotor1PWM >> 8);
    wBuf[3] = (uint8_t)(realMotor2PWM);
    wBuf[4] = (uint8_t)(realMotor2PWM >> 8);

    bcm2835_i2c_write(wBuf, 5);
}

/**
 * Motor A is the Left motor on the robot, Motor B is the Right one
 * @param maPWM
 * @param mbPWM
 */
void Motors::drivePWM(float _leftPWM, float _rightPWM){
    // We stablish a negative relationship with the PWM of the LEFT motor, this way 
    // we obtain a proper behavior for a robot:
    // - Positive PWM => forward motion (CCW)
    // - negative PWM => backward motion (CW)
    if(leftMotor == MOTORS_MOTOR1_CONN and rightMotor == MOTORS_MOTOR2_CONN){
        motorsPWM(-_leftPWM, _rightPWM);
    }else{
        if(leftMotor == MOTORS_MOTOR2_CONN and rightMotor == MOTORS_MOTOR1_CONN){
            motorsPWM(_rightPWM,-_leftPWM);
        }else
            printf("MotorModule Error!!... Wrong motor configuration\n");
    }            
}

//void Motors::configPause(){
//    uDelay(20);    
//}

int16_t Motors::constrainPWM(float value){
    int16_t roundedValue = (int16_t)std::round(value*10.0f);
    roundedValue = constrain(roundedValue, -MOTORS_MAX_SPEED, MOTORS_MAX_SPEED);
    return roundedValue;
}

int16_t Motors::constrain(int16_t value, int16_t min, int16_t max){
    if(value > max){
        return max;
    }
    
    if(value < min){
        return min;
    }
    
    return value;
}

void Motors::bcm_init(){
    // - 400kHz aproximadamente...
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_626;
    // - La direccion del esclavo se establece en cada modulo

    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }
    
    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
}

void Motors::bcm_end(){
    bcm2835_i2c_end();
    bcm2835_close();    
}

void Motors::release(){
    motorsControl(MOTORS_STOP,MOTORS_STOP);
    printf("[MotorsModule] => Released\n");
}