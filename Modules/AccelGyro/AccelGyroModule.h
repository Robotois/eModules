/* 
 * File:   AccelGyroModule.h
 * Author: yova
 *
 * Created on 23 de febrero de 2016, 08:39 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>
#include <math.h>
#include <iostream>
#include <fstream>
//#include <armadillo>

#ifndef ACCELGYROMODULE_H
#define	ACCELGYROMODULE_H

#define RAD_TO_DEG 180.0f/M_PI

/**
 * MPU Registers
 */
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18

struct Measurement{
    int16_t xValue;
    int16_t yValue;
    int16_t zValue;
};

using namespace std;
//using namespace arma;

class AccelGyroModule {

public:
    uint8_t GYRO_FS_SEL,ACCEL_FS_SEL;
    Measurement accelMeas,gyroMeas;
    
    AccelGyroModule();
    AccelGyroModule(const AccelGyroModule& orig);
    virtual ~AccelGyroModule();
    
    void selectModule();
    void initialize();
    bool testConnection();
    void calibrateMPU();
    void resetDevice();
    void xGyroClockSource();
    
    void getAccelMeas();
    void getGyroMeas();
    void getMeas();
    float getRoll();

    float getXAngle();
    float getYAngle();
    float getXGyro();
    float getYGyro();
    
    // - KalmanFilter Functions
    void kalman_yInit(float dt);
    float kalman_yAngle();
    
    // - Plotting variables
    string fileName;
    // - CSV Dataset
//    float pos,poshat,posmeas, vel, velhat;
    // - Archivo CSV con los resultados del filtro.
    ofstream outputFile;
    uint16_t t;
    
    float accelX,accelY,accelZ;

    void setXAccelOffset(uint16_t offset);
    void setYAccelOffset(uint16_t offset);
    void setZAccelOffset(uint16_t offset);
    void setXGyroOffset(uint16_t offset);
    void setYGyroOffset(uint16_t offset);
    void setZGyroOffset(uint16_t offset);
    
private:
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
    static const float gyroScaleFactors[],accelScaleFactors[];
    // - MPU6050 Registers
    static const uint8_t PWR_MGMT_1 = 0x6B, SAMPLE_RATE_DIVIDER = 0x19,CONFIG = 0x1A,
            GYRO_CONFIG = 0x1B, ACCEL_CONFIG = 0x1C,
            ACCEL_XOUT_H = 0x3B, ACCEL_XOUT_L = 0x3C, ACCEL_YOUT_H = 0x3D, 
            ACCEL_YOUT_L = 0x3E, ACCEL_ZOUT_H = 0x3F, ACCEL_ZOUT_L = 0x40,
            GYRO_XOUT_H = 0x43, GYRO_XOUT_L = 0x44, GYRO_YOUT_H = 0x45, 
            GYRO_YOUT_L = 0x46, GYRO_ZOUT_H = 0x47, GYRO_ZOUT_L = 0x48;
    uint8_t slave_address,result,debugButton;
    // - MPU6050_init
    char rBuf[16]; // - Max length
    char wBuf[16]; // - Max length
    float accelScaleFactor,gyroScaleFactor;
    
    float axisAngle(int accMeas, int zRef);
    int fullRangeMeas(uint16_t reading);
    
    // - Kalman Filter Variables
    float measnoise,accelNoise,driftNoise,u,Sz;
//    fmat A,s,K,Sw,P;
//    fvec B,x,y,Inn,x_hat;
//    frowvec C;
    
    // - Calibation variables
    //Change this 3 variables if you want to fine tune the skecth to your needs.
    int buffersize;     //Amount of readings used to average, make it higher to get more precision but sketch will be slower  (default:1000)
    int acel_deadzone;     //Acelerometer error allowed, make it lower to get more precision, but sketch may not converge  (default:8)
    int giro_deadzone;     //Giro error allowed, make it lower to get more precision, but sketch may not converge  (default:1)

    int16_t ax, ay, az,gx, gy, gz;

    int mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz,state;
    int ax_offset,ay_offset,az_offset,gx_offset,gy_offset,gz_offset;
    
       
    int16_t getXAccelOffset();
    int16_t getYAccelOffset();
    int16_t getZAccelOffset();
    int16_t getXGyroOffset();
    int16_t getYGyroOffset();
    int16_t getZGyroOffset();
    
    void calibrateLoop();
    void meansensors();
    void calibration();
    void getMotion6(int16_t *ax,int16_t *ay,int16_t *az,int16_t *gx,int16_t *gy,int16_t *gz);
};

#endif	/* ACCELGYROMODULE_H */

