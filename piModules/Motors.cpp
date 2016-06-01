/* 
 * File:   Motors.cpp
 * Author: yova
 * 
 * Created on 26 de enero de 2016, 06:15 PM
 */

#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Motors.h"
#include "Libraries/Timer/AccurateTiming.h"
//#include <bcm2835.h>

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
    wBuf[0] = 0x1F;
//    wBuf[1] = (revCounts & 0xFF);
//    wBuf[2] = 0x0D;
//    wBuf[3] = (revCounts & 0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf, 1);
//    configPause();
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
    wBuf[0] = 0x00; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
//    configPause(); 
}

/**
 * Establece el PWM del motor A.
 * @param pwmReal => Valor de PWM en un rango de 0-100, con un digito decimal,
 * con lo que se obtienen 1000 velocidades.
 */
void Motors::maPWM(float pwmReal){
    uint16_t pwm;
    uint8_t result;
    pwm = (uint16_t)(pwmReal * 10.0);
    wBuf[0] = 0x02;
    wBuf[1] = (pwm & 0xFF);
//    wBuf[2] = 0x03;
    wBuf[2] = (pwm & 0xFF00)>>8;

    result = bcm2835_i2c_write(wBuf, 3);
    printf("PWM Result: %d\n",result);
//    configPause();
}

/**
 * Configura la velocidad deseada en el motor A.
 * @param rpm => Velocidad en RPM.
 */
void Motors::maSpeed(uint16_t rpm){
    wBuf[0] = 0x06;
    wBuf[1] = (rpm&0xFF);
//    wBuf[2] = 0x07;
    wBuf[2] = (rpm&0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf,3);    
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
    wBuf[0] = 0x01; // - Direccion del registro
    wBuf[1] = control; // - Contenido del registro
    bcm2835_i2c_write(wBuf, 2);
//    configPause(); 
}

void Motors::motorsControl(uint8_t maControl, uint8_t mbControl){
    wBuf[0] = 0x00; // - Direccion del registro
    wBuf[1] = maControl; // - Contenido del registro
    wBuf[2] = mbControl; // - Contenido del registro
    bcm2835_i2c_write(wBuf,3);
//    configPause();     
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
//    wBuf[2] = 0x05;
    wBuf[2] = (pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 3);
//    configPause();
}

/**
 * Configura la velocidad deseada en el motor B.
 * @param rpm => Velocidad en RPM.
 */
void Motors::mbSpeed(uint16_t rpm){
    wBuf[0] = 0x08;
    wBuf[1] = (rpm&0xFF);
//    wBuf[2] = 0x09;
    wBuf[2] = (rpm&0xFF00)>>8;
    
    bcm2835_i2c_write(wBuf,3);    
    configPause();
}

void Motors::motorsPWM(float maPWM, float mbPWM){
    uint16_t pwm;
    
    pwm = (uint16_t)(maPWM * 10.0);
    wBuf[0] = 0x02;
    wBuf[1] = (pwm & 0xFF);
//    wBuf[2] = 0x03;
    wBuf[2] = (pwm & 0xFF00)>>8;

    pwm = (uint16_t)(mbPWM * 10.0);
//    wBuf[4] = 0x04;
    wBuf[3] = (pwm & 0xFF);
//    wBuf[6] = 0x05;
    wBuf[4] = (pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 5);
    configPause();
}

void Motors::motorsPWM2(int maPWM, int mbPWM){
    
    if(maPWM> 1000){
        maPWM = 1000;
    }
    
    if(maPWM < -1000){
        maPWM = -1000;
    }
    
    if(maPWM < 0 ){
        ma_pwm = (uint16_t)abs(maPWM);
        ma_pwm ^= 0x8000;
    }else{
        ma_pwm = (uint16_t)maPWM;
    }
    
//    printf("Inputs: 0x%04X\n",ma_pwm);
//    if(ma_pwm & (1 << 15)){
//        cout<<"Negative!!"<<endl;
//    }
    if(mbPWM> 1000){
        mbPWM = 1000;
    }
    
    if(mbPWM < -1000){
        mbPWM = -1000;
    }
    
    if(mbPWM < 0 ){
        mb_pwm = (uint16_t)abs(mbPWM);
        mb_pwm ^= 0x8000;
    }else{
        mb_pwm = (uint16_t)mbPWM;
    }

    wBuf[0] = 0x02;
    wBuf[1] = (ma_pwm & 0x00FF);
//    wBuf[2] = 0x03;
    wBuf[2] = (ma_pwm & 0xFF00)>>8;

//    wBuf[4] = 0x04;
    wBuf[3] = (mb_pwm & 0x00FF);
//    wBuf[6] = 0x05;
    wBuf[4] = (mb_pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 5);
    configPause();
}

/**
 * Motor A is the Left motor on the robot, Motor B is the Right one
 * @param maPWM
 * @param mbPWM
 */
void Motors::drivePWMs(int maPWM, int mbPWM){
//    uint16_t ma_pwm, mb_pwm;    
    if(maPWM> 1000){
        maPWM = 1000;
    }
    
    if(maPWM < -1000){
        maPWM = -1000;
    }
    
    if(maPWM < 0 ){ // - For negative PWM move Backwards, on Left Motor => Clockwise
        ma_pwm = (uint16_t)abs(maPWM);
    }else{ // - For positive PWM move Forward, on Left Motor => Counter Clockwise
        ma_pwm = (uint16_t)maPWM;
        ma_pwm ^= 0x8000;
    }
    
//    printf("Inputs: 0x%04X\n",ma_pwm);
//    if(ma_pwm & (1 << 15)){
//        cout<<"Negative!!"<<endl;
//    }
    if(mbPWM> 1000){
        mbPWM = 1000;
    }
    
    if(mbPWM < -1000){
        mbPWM = -1000;
    }
    
    if(mbPWM < 0 ){ // - For negative PWM move Backwards, on Right Motor => Clockwise
        mb_pwm = (uint16_t)abs(mbPWM);
        mb_pwm ^= 0x8000;
    }else{ // - For positive PWM move Forward, on Left Motor => Counter Clockwise
        mb_pwm = (uint16_t)mbPWM;
    }

    wBuf[0] = 0x02;
    wBuf[1] = (ma_pwm & 0x00FF);
//    wBuf[2] = 0x03;
    wBuf[2] = (ma_pwm & 0xFF00)>>8;

//    wBuf[4] = 0x04;
    wBuf[3] = (mb_pwm & 0x00FF);
//    wBuf[6] = 0x05;
    wBuf[4] = (mb_pwm & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 5);
//    configPause();
}

void Motors::driveSpeeds(int maSpeed, int mbSpeed){
//    uint16_t ma_pwm, mb_pwm;    
    if(maSpeed > 1000){
        maSpeed = 1000;
    }
    
    if(maSpeed < -1000){
        maSpeed = -1000;
    }
    
    if(maSpeed < 0 ){ // - For negative Speed move Backwards, on Left Motor => Clockwise
        ma_speed = (uint16_t)abs(maSpeed);
    }else{ // - For positive Speed move Forward, on Left Motor => Counter Clockwise
        ma_speed = (uint16_t)maSpeed;
        ma_speed ^= 0x8000;
    }
    
//    printf("Inputs: 0x%04X\n",ma_pwm);
//    if(ma_pwm & (1 << 15)){
//        cout<<"Negative!!"<<endl;
//    }
    if(mbSpeed> 1000){
        mbSpeed = 1000;
    }
    
    if(mbSpeed < -1000){
        mbSpeed = -1000;
    }
    
    if(mbSpeed < 0 ){ // - For negative Speed move Backwards, on Right Motor => Counter Clockwise
        mb_speed = (uint16_t)abs(mbSpeed);
        mb_speed ^= 0x8000;
    }else{ // - For positive Speed move Forward, on Left Motor => Clockwise
        mb_speed = (uint16_t)mbSpeed;
    }
    
//    pwm = (uint16_t)(maPWM * 10.0);
    wBuf[0] = 0x06;
    wBuf[1] = (ma_speed & 0xFF);
//    wBuf[2] = 0x03;
    wBuf[2] = (ma_speed & 0xFF00)>>8;

//    pwm = (uint16_t)(mbPWM * 10.0);
//    wBuf[4] = 0x04;
    wBuf[3] = (mb_speed & 0xFF);
//    wBuf[6] = 0x05;
    wBuf[4] = (mb_speed & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 5);
//    configPause();
}

void Motors::motorsSpeed(uint16_t maSpeed, uint16_t mbSpeed){
//    uint16_t pwm;
    
//    pwm = (uint16_t)(maPWM * 10.0);
    wBuf[0] = 0x06;
    wBuf[1] = (maSpeed & 0xFF);
//    wBuf[2] = 0x03;
    wBuf[2] = (maSpeed & 0xFF00)>>8;

//    pwm = (uint16_t)(mbPWM * 10.0);
//    wBuf[4] = 0x04;
    wBuf[3] = (mbSpeed & 0xFF);
//    wBuf[6] = 0x05;
    wBuf[4] = (mbSpeed & 0xFF00)>>8;

    bcm2835_i2c_write(wBuf, 5);
    configPause();
}

void Motors::GetEncoderTicks(long* LeftEncoderTicks, long* RightEncoderTicks){
    wBuf[0] = 0x25;
    bcm2835_i2c_write(wBuf,1);    
    bcm2835_i2c_read(rBuf,8);
    
    *LeftEncoderTicks = (rBuf[3] >> 24) | (rBuf[2] >> 16) | (rBuf[1] >> 8) | (rBuf[0]);
    *RightEncoderTicks = (rBuf[7] >> 24) | (rBuf[6] >> 16) | (rBuf[5] >> 8) | (rBuf[4]);    
}

void Motors::ResetEncoderCounters(){
    wBuf[0] = 0x24;
    bcm2835_i2c_write(wBuf,1);    
}

void Motors::configPause(){
    uDelay(50);    
}


// -- Motors Test
void Motors::motorsBasicTest(){
//    maControl(clockwise);
    motorsPWM2(250,250); // - Left Motor
    sleep(3);
    motorsPWM2(500,500); // - Left Motor
    sleep(3);
    motorsPWM2(750,750); // - Left Motor
    sleep(3);
    motorsPWM2(1000,1000); // - Left Motor
    sleep(3);
    motorsPWM2(0,0); // - Left Motor
    sleep(3);
    motorsPWM2(-250,-250); // - Left Motor
    sleep(3);
    motorsPWM2(-500,-500); // - Left Motor
    sleep(3);
    motorsPWM2(-750,-750); // - Left Motor
    sleep(3);
    motorsPWM2(-1000,-1000); // - Left Motor
    sleep(3);
    motorsPWM2(0,0); // - Left Motor
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