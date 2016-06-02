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

#include "Motors.h"
#include "../../Libraries/Timer/AccurateTiming.h"
#include <bcm2835.h>

using namespace std;

Motors::Motors() {
    slave_address = 0x10; // - Direccion por default
//    clockwise = 2;
//    counter_clockwise = 1;
//    stop = 0;    
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
void Motors::motorsSetup25D(){
    selectModule();
    wBuf[0] = 0x1F;
    bcm2835_i2c_write(wBuf, 1);
}


/**
 * Se establece la configuracion del motor A.
 * @param gearBox => Relacion de vueltas del gearBox.
 */
void Motors::maSetup(float gearBox){
    selectModule();
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
    selectModule();
    wBuf[0] = 0x00; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
}

/**
 * Establece el PWM del motor A.
 * @param pwmReal => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::maPWM(int16_t pwmReal){
    selectModule();
    
    constrain(&pwmReal,-1000,1000);
    wBuf[0] = 0x02;
    wBuf[1] = (uint8_t)pwmReal;
    wBuf[2] = (uint8_t)(pwmReal >> 8);

    bcm2835_i2c_write(wBuf, 3);
}

/**
 * Configura la velocidad deseada en el motor A.
 * @param rpm => Velocidad en RPM.
 */
void Motors::maSpeed(int16_t rpm){
    selectModule();

    constrain(&rpm,-500,500);
    wBuf[0] = 0x06;
    wBuf[1] = (uint8_t)rpm;
    wBuf[2] = (uint8_t)(rpm >> 8);
    
    bcm2835_i2c_write(wBuf,3);    
}

/**
 * Se establece la configuracion del motor B.
 * @param gearBox => Relacion de vueltas del gearBox.
 */
void Motors::mbSetup(float gearBox){
    selectModule();
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
    selectModule();
    wBuf[0] = 0x01; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
}

void Motors::motorsControl(uint8_t maControl, uint8_t mbControl){
    selectModule();
    wBuf[0] = 0x00; // - Direccion del registro
    wBuf[1] = maControl; // - Contenido del registro
    wBuf[2] = mbControl; // - Contenido del registro
    bcm2835_i2c_write(wBuf,3);
}

/**
 * Establece el PWM del motor B.
 * @param pwmReal => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::mbPWM(int16_t pwmReal){
    selectModule();
    
    constrain(&pwmReal,-1000,1000);
    wBuf[0] = 0x04;
    wBuf[1] = (uint8_t)pwmReal;
    wBuf[2] = (uint8_t)(pwmReal >> 8);

    bcm2835_i2c_write(wBuf, 3);
}

/**
 * Configura la velocidad deseada en el motor B.
 * @param rpm => Velocidad en RPM.
 */
void Motors::mbSpeed(int16_t rpm){
    selectModule();
    
    constrain(&rpm,-500,500);
    wBuf[0] = 0x08;
    wBuf[1] = (uint8_t)rpm;
    wBuf[2] = (uint8_t)(rpm >> 8);
    
    bcm2835_i2c_write(wBuf,3);    
}

void Motors::motorsPWM(int16_t maPWM, int16_t mbPWM){
    selectModule();

    constrain(&maPWM,-1000,1000);
    constrain(&mbPWM,-1000,1000);

    wBuf[0] = 0x02;
    wBuf[1] = (uint8_t)maPWM;
    wBuf[2] = (uint8_t)(maPWM >> 8);
    wBuf[3] = (uint8_t)(mbPWM);
    wBuf[4] = (uint8_t)(mbPWM >> 8);

    bcm2835_i2c_write(wBuf, 5);
}

/**
 * Motor A is the Left motor on the robot, Motor B is the Right one
 * @param maPWM
 * @param mbPWM
 */
void Motors::drivePWMs(int16_t maPWM, int16_t mbPWM){
    selectModule();
    constrain(&maPWM,-1000,1000);
    constrain(&mbPWM,-1000,1000);
    // The motor module drives the motors in Clockwise direction when the PWM parammeter
    // is positive, it drives them CounterClockwise when a negative PWM is provided.
    
    // We stablish a negative relationship with the PWM of the LEFT motor, this way 
    // we obtain a proper behavior for a robot:
    // - Positive PWM => forward motion (CCW)
    // - negative PWM => backward motion (CW)
    ma_pwm = -maPWM;
    // For the right motor there is a direct relationship with the PWM parammeter.
    mb_pwm = mbPWM;
    
    wBuf[0] = 0x02;
    wBuf[1] = (uint8_t)ma_pwm;
    wBuf[2] = (uint8_t)(ma_pwm >> 8);
    wBuf[3] = (uint8_t)(mb_pwm);
    wBuf[4] = (uint8_t)(mb_pwm >> 8);

    bcm2835_i2c_write(wBuf, 5);
}

void Motors::driveSpeeds(int16_t maSpeed, int16_t mbSpeed){
    selectModule();

    constrain(&maSpeed,-500,500);
    constrain(&mbSpeed,-500,500);

    ma_speed = -maSpeed;
    mb_speed = mbSpeed;
    
    wBuf[0] = 0x06;
    wBuf[1] = (uint8_t)ma_speed;
    wBuf[2] = (uint8_t)(ma_speed >> 8);
    wBuf[3] = (uint8_t)(mb_speed);
    wBuf[4] = (uint8_t)(mb_speed >> 8);

    bcm2835_i2c_write(wBuf, 5);
}

void Motors::motorsSpeed(int16_t maSpeed, int16_t mbSpeed){
    selectModule();
    constrain(&maSpeed,-500,500);
    constrain(&mbSpeed,-500,500);

    wBuf[0] = 0x06;
    wBuf[1] = (uint8_t)maSpeed;
    wBuf[2] = (uint8_t)(maSpeed >> 8);
    wBuf[3] = (uint8_t)(mbSpeed);
    wBuf[4] = (uint8_t)(mbSpeed >> 8);

    bcm2835_i2c_write(wBuf, 5);
}

void Motors::GetEncoderTicks(long* LeftEncoderTicks, long* RightEncoderTicks){
    selectModule();
    wBuf[0] = 0x25;
    bcm2835_i2c_write(wBuf,1);    
    bcm2835_i2c_read(rBuf,8);
    
    *LeftEncoderTicks = (rBuf[3] >> 24) | (rBuf[2] >> 16) | (rBuf[1] >> 8) | (rBuf[0]);
    *RightEncoderTicks = (rBuf[7] >> 24) | (rBuf[6] >> 16) | (rBuf[5] >> 8) | (rBuf[4]);    
}

void Motors::ResetEncoderCounters(){
    selectModule();
    wBuf[0] = 0x24;
    bcm2835_i2c_write(wBuf,1);    
}

void Motors::configPause(){
    uDelay(50);    
}


// -- Motors Test
void Motors::motorsBasicTest(){
//    maControl(clockwise);
    drivePWMs(250,250); // - Left Motor
    sleep(3);
    drivePWMs(500,500); // - Left Motor
    sleep(3);
    drivePWMs(750,750); // - Left Motor
    sleep(3);
//    drivePWMs(1000,1000); // - Left Motor
//    sleep(3);
    drivePWMs(0,0); // - Left Motor
    sleep(3);
    drivePWMs(-250,-250); // - Left Motor
    sleep(3);
    drivePWMs(-500,-500); // - Left Motor
    sleep(3);
    drivePWMs(-750,-750); // - Left Motor
    sleep(3);
//    drivePWMs(-1000,-1000); // - Left Motor
//    sleep(3);
    drivePWMs(0,0); // - Left Motor
}

void Motors::motorsBasicSpeedTest(){
//    maControl(clockwise);
    driveSpeeds(50,50); // - Left Motor
    sleep(3);
    driveSpeeds(100,100); // - Left Motor
    sleep(3);
    driveSpeeds(200,200); // - Left Motor
    sleep(3);
//    drivePWMs(1000,1000); // - Left Motor
//    sleep(3);
    driveSpeeds(0,0); // - Left Motor
    sleep(3);
    driveSpeeds(-50,-50); // - Left Motor
    sleep(3);
    driveSpeeds(-100,-100); // - Left Motor
    sleep(3);
    driveSpeeds(-200,-200); // - Left Motor
    sleep(3);
//    drivePWMs(-1000,-1000); // - Left Motor
//    sleep(3);
    driveSpeeds(0,0); // - Left Motor
}

// --- Motors Test
// -- MOTOR A TEST
void Motors::maBasicTest(){
    maControl(clockwise);
    maPWM(25); // - Left Motor
    sleep(5);
    maPWM(50); // - Left Motor
    sleep(5);
    maPWM(75); // - Left Motor
    sleep(5);
    maPWM(100); // - Left Motor
    sleep(5);
    maPWM(0); // - Left Motor

    maControl(counter_clockwise);
    maPWM(25); // - Left Motor
    sleep(5);
    maPWM(50); // - Left Motor
    sleep(5);
    maPWM(75); // - Left Motor
    sleep(5);
    maPWM(100); // - Left Motor
    sleep(5);
    maPWM(0); // - Left Motor    
}

void Motors::maFullSpeedTest(){
    selectModule();    
    char buf[250];
    wBuf[0] = 0x20;

    string fileName = "maFullSpeedResponse.csv";
    // - CSV Dataset
    // - Archivo CSV con los resultados.
    ofstream outputFile(fileName.c_str(),ios_base::out);    
    // - Plotting DataSet
//    fileName = "maFullSpeedResponse.csv";
//    outputFile.open(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    outputFile<<"\"Time\",\"EncCounts\""<<endl;    
        
    bcm2835_i2c_write(wBuf,1);    
    sleep(5);
    bcm2835_i2c_read(buf,250);
    for(int i = 0; i < 250; i++){
        printf("[%d] => %d\n",i,(unsigned char)buf[i]);
        outputFile<<i<<','<<(int)buf[i]<<endl;
    }
    outputFile.close();
}

void Motors::maPIDResponse(){
    selectModule();    
    char buf[250];
    wBuf[0] = 0x21;

    string fileName = "maPIDResponse.csv";
    // - CSV Dataset
    // - Archivo CSV con los resultados.
    ofstream outputFile(fileName.c_str(),ios_base::out);    
    // - Plotting DataSet
//    fileName = "maFullSpeedResponse.csv";
//    outputFile.open(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    outputFile<<"\"Time\",\"EncCounts\""<<endl;    
        
    bcm2835_i2c_write(wBuf,1);    
    sleep(5);
    bcm2835_i2c_read(buf,250);
    for(int i = 0; i < 250; i++){
        printf("[%d] => %d\n",i,(unsigned char)buf[i]);
        outputFile<<i<<','<<(int)buf[i]<<endl;
    }
    outputFile.close();
}

// -- MOTOR B TEST
void Motors::mbBasicTest(){
    mbControl(clockwise);
    mbPWM(25); // - Left Motor
    sleep(5);
    mbPWM(50); // - Left Motor
    sleep(5);
    mbPWM(75); // - Left Motor
    sleep(5);
    mbPWM(100); // - Left Motor
    sleep(5);
    mbPWM(0); // - Left Motor

    mbControl(counter_clockwise);
    mbPWM(25); // - Left Motor
    sleep(5);
    mbPWM(50); // - Left Motor
    sleep(5);
    mbPWM(75); // - Left Motor
    sleep(5);
    mbPWM(100); // - Left Motor
    sleep(5);
    mbPWM(0); // - Left Motor    
}

void Motors::mbFullSpeedTest(){
    selectModule();
    char buf[250];
    wBuf[0] = 0x22;

    string fileName = "mbFullSpeedResponse.csv";
    // - CSV Dataset
    // - Archivo CSV con los resultados.
    ofstream outputFile(fileName.c_str(),ios_base::out);    
    // - Plotting DataSet
//    fileName = "maFullSpeedResponse.csv";
//    outputFile.open(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    outputFile<<"\"Time\",\"EncCounts\""<<endl;    
        
    bcm2835_i2c_write(wBuf,1);    
    sleep(5);
    bcm2835_i2c_read(buf,250);
    for(int i = 0; i < 250; i++){
        printf("[%d] => %d\n",i,(unsigned char)buf[i]);
        outputFile<<i<<','<<(int)buf[i]<<endl;
    }
    outputFile.close();
}

void Motors::mbPIDResponse(){
    selectModule();    
    char buf[250];
    wBuf[0] = 0x23;

    string fileName = "mbPIDResponse.csv";
    // - CSV Dataset
    // - Archivo CSV con los resultados.
    ofstream outputFile(fileName.c_str(),ios_base::out);    
    // - Plotting DataSet
//    fileName = "maFullSpeedResponse.csv";
//    outputFile.open(fileName.c_str(),ios_base::out);
    if ( ! outputFile.is_open() ){    
        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
        exit(1);
    }
    outputFile<<"\"Time\",\"EncCounts\""<<endl;    
        
    bcm2835_i2c_write(wBuf,1);    
    sleep(5);
    bcm2835_i2c_read(buf,250);
    for(int i = 0; i < 250; i++){
        printf("[%d] => %d\n",i,(unsigned char)buf[i]);
        outputFile<<i<<','<<(int)buf[i]<<endl;
    }
    outputFile.close();
}

void Motors::constrain(int16_t* value, int16_t min, int16_t max){
    if(*value > max){
        *value = max;
        return;
    }
    
    if(*value < min){
        *value = min;
        return;
    }    
}