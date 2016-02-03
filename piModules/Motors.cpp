/* 
 * File:   Motors.cpp
 * Author: yova
 * 
 * Created on 26 de enero de 2016, 06:15 PM
 */

#include <unistd.h>

#include "Motors.h"
//#include <bcm2835.h>

Motors::Motors() {
    slave_address = 0x10; // - Direccion por default
    clockwise = 2;
    counter_clockwise = 1;
    stop = 0;    
}

Motors::Motors(const Motors& orig) {
}

Motors::~Motors() {
}

/**
 * Reestablece la direccion del esclavo en l puerto i2c. Se debe llamar antes de
 * iniciar una transaccion o serie de transacciones hacia el modulo de motores.
 */
void Motors::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_address);
}

/**
 * Se establece la configuracion del motor A.
 * @param gearBox => Relacion de vueltas del gearBox.
 */
void Motors::maSetup(float gearBox){
    uint16_t revCounts;
    revCounts = (uint16_t)(gearBox*6.0); // - Conteo del encoder por vuelta del rotor
    // - Registros para configurar el gearBox son de 8 bits
    wBuf[0] = 0x0C;
    wBuf[1] = (revCounts & 0xFF);
    wBuf[2] = 0x0D;
    wBuf[3] = (revCounts & 0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf, 4);
    configPause();
}

/**
 * Establece el sentido de giro y permite detener el motor A.
 * @param control => 0 --> Stop, 1 --> counter_clockwise, 2 --> clockwise.
 */
void Motors::maControl(uint8_t control){
    wBuf[0] = 0x0A; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
    configPause(); 
}

/**
 * Establece el PWM del motor A.
 * @param pwmReal => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::maPWM(float pwmReal){
    uint16_t pwm;
    
    pwm = (uint16_t)(pwmReal * 10.0);
    wBuf[0] = 0x02;
    wBuf[1] = (pwm & 0xFF);
    wBuf[2] = 0x03;
    wBuf[3] = (pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 4);
    configPause();
}

/**
 * Configura la velocidad deseada en el motor A.
 * @param rpm => Velocidad en RPM.
 */
void Motors::maSpeed(uint16_t rpm){
    wBuf[0] = 0x06;
    wBuf[1] = (rpm&0xFF);
    wBuf[2] = 0x07;
    wBuf[3] = (rpm&0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf,4);    
    configPause();
}

/**
 * Se establece la configuracion del motor B.
 * @param gearBox => Relacion de vueltas del gearBox.
 */
void Motors::mbSetup(float gearBox){
    uint16_t revCounts;
    revCounts = (uint16_t)(gearBox*6.0); // - Conteo del encoder por vuelta del rotor
    // - Registros para configurar el gearBox son de 8 bits
    wBuf[0] = 0x0E;
    wBuf[1] = (revCounts & 0x00FF);
    wBuf[2] = 0x0F;
    wBuf[3] = (revCounts & 0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf, 4);
    configPause();
}

/**
 * Establece el sentido de giro y permite detener el motor B.
 * @param control => 0 --> Stop, 1 --> counter_clockwise, 2 --> clockwise.
 */
void Motors::mbControl(uint8_t control){
    wBuf[0] = 0x0B; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
    configPause(); 
}

/**
 * Establece el PWM del motor B.
 * @param pwmReal => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::mbPWM(float pwmReal){
    uint16_t pwm;
    
    pwm = (uint16_t)(pwmReal * 10.0);
    wBuf[0] = 0x04;
    wBuf[1] = (pwm & 0xFF);
    wBuf[2] = 0x05;
    wBuf[3] = (pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 4);
    configPause();
}

/**
 * Configura la velocidad deseada en el motor B.
 * @param rpm => Velocidad en RPM.
 */
void Motors::mbSpeed(uint16_t rpm){
    wBuf[0] = 0x08;
    wBuf[1] = (rpm&0xFF);
    wBuf[2] = 0x09;
    wBuf[3] = (rpm&0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf,4);    
    configPause();
}

void Motors::configPause(){
    usleep(50);    
}

void Motors::maStepResponse(){
    char buf[200];
    wBuf[0] = 0x10;
//    wBuf[1] = ;
//    wBuf[2] = 0x09;
//    wBuf[3] = (rpm&0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf,1);    
    configPause();
    bcm2835_i2c_read(buf,200);
    for(int i = 0; i < 200; i++){
        printf("[%d] => %d\n",i,(unsigned char)buf[i]);
    }
}

void Motors::motorsPWM(float maPWM, float mbPWM){
    uint16_t pwm;
    
    pwm = (uint16_t)(maPWM * 10.0);
    wBuf[0] = 0x02;
    wBuf[1] = (pwm & 0xFF);
    wBuf[2] = 0x03;
    wBuf[3] = (pwm & 0xFF00)>>8;

    pwm = (uint16_t)(mbPWM * 10.0);
    wBuf[4] = 0x04;
    wBuf[5] = (pwm & 0xFF);
    wBuf[6] = 0x05;
    wBuf[7] = (pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 8);
    configPause();
}