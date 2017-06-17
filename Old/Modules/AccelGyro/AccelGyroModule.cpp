/* 
 * File:   AccelGyroModule.cpp
 * Author: yova
 * 
 * Created on 23 de febrero de 2016, 08:39 PM
 */

#include <math.h>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <bcm2835.h>

#include "AccelGyroModule.h"
#include "../../Libraries/Timer/AccurateTiming.h"

const float AccelGyroModule::gyroScaleFactors[] = {131,65.5,32.8,16.4};
const float AccelGyroModule::accelScaleFactors[] = {16384,8192,4096,2048};

AccelGyroModule::AccelGyroModule() {
    GYRO_FS_SEL = 0;
    ACCEL_FS_SEL = 0;
    slave_address = 0x69;
    accelScaleFactor = accelScaleFactors[ACCEL_FS_SEL];
    gyroScaleFactor = gyroScaleFactors[GYRO_FS_SEL];
}

AccelGyroModule::AccelGyroModule(const AccelGyroModule& orig) {
}

AccelGyroModule::~AccelGyroModule() {
}

void AccelGyroModule::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_address);        
}

void AccelGyroModule::initialize(){
    selectModule();
    xGyroClockSource();
    wBuf[0] = SAMPLE_RATE_DIVIDER;
    wBuf[1] = 0x07; // - Sample Rate = 1[kHz] / (1 + 4) = 200[Hz] => 5[ms]
//    result = bcm2835_i2c_write(wBuf, 2);
//    wBuf[0] = CONFIG;
    wBuf[2] = 0x00; // - Acc => Bandwidth: 44[Hz], Delay: 4.9[ms]; Gyro => Bandwidth: 42[Hz], Delay:  4.8[ms]; FS: 1[kHz]
//    result = bcm2835_i2c_write(wBuf, 2);
    // - Full Scale Gyro/Accel Ranges
//    wBuf[0] = GYRO_CONFIG; // - Gyro and Accel config registers have consecutive addresses
    wBuf[3] = GYRO_FS_SEL;
    wBuf[4] = ACCEL_FS_SEL;
    result = bcm2835_i2c_write(wBuf, 5);
    

    // - Sleep Enable => false
    uint8_t tempReg;
    wBuf[0] = PWR_MGMT_1;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    tempReg = rBuf[0] & 0xBF;

    wBuf[1] = tempReg;
    bcm2835_i2c_write(wBuf,2);

    setXAccelOffset((int16_t)-2422);
    setYAccelOffset((int16_t)-607);
    setZAccelOffset((int16_t)629);
    setXGyroOffset((int16_t)136);
    setYGyroOffset((int16_t)-74);
    setZGyroOffset((int16_t)-55);        
}

void AccelGyroModule::resetDevice(){
//    bcm2835_i2c_setSlaveAddress(accelGyroAddress);   
    // Reset device, this resets all internal registers to their default values
    wBuf[0] = PWR_MGMT_1;
    wBuf[1] = 0x80;
    bcm2835_i2c_write(wBuf, 2);
    
    do{
//        wBuf[0] = 0x6B;
        bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    } while (rBuf[0] & 0x80); // Wait for the bit to clear
    mDelay(100);    
}

void AccelGyroModule::xGyroClockSource(){
    uint8_t tempReg;
    wBuf[0] = PWR_MGMT_1;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    tempReg = (rBuf[0] & 0xF0) | 0x09; // - Also Disable Temp Sensor

    wBuf[1] = tempReg;
    bcm2835_i2c_write(wBuf,2);
}

void AccelGyroModule::calibrateMPU(){
    debugButton = RPI_V2_GPIO_P1_13;
    bcm2835_gpio_fsel(debugButton,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(debugButton, BCM2835_GPIO_PUD_DOWN);
    bcm2835_gpio_aren(debugButton);
    
    buffersize=1000;    
    acel_deadzone=8;
    giro_deadzone=1;
    state=0;
    
//    printf("Press Debug Button to start Calibration...\n");
//    while(!bcm2835_gpio_eds(debugButton));
//    bcm2835_gpio_set_eds(debugButton);
//    mDelay(500);
    
    // start message
    printf("\nMPU6050 Calibration Sketch\n");
//    delay(2000);
    printf("\nYour MPU6050 should be placed in horizontal position, with package "
            "letters facing up. \nDon't touch it until you see a finish message.\n");
    printf("Press Debug Button to Continue...\n\n");
//    while(!bcm2835_gpio_eds(debugButton));
//    bcm2835_gpio_set_eds(debugButton);
//    mDelay(500);

    // verify connection
    selectModule();
    
    resetDevice();
    initialize();
    printf(testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    sleep(1);
    // reset offsets
    setXAccelOffset(0);
    setYAccelOffset(0);
    setZAccelOffset(0);
    setXGyroOffset(0);
    setYGyroOffset(0);
    setZGyroOffset(0);    

//    getXAccelOffset();
//    getYAccelOffset();
//    getZAccelOffset();
//    getXGyroOffset();
//    getYGyroOffset();
//    getZGyroOffset();    
    
    printf("Initial Offsets: \n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",getXAccelOffset(),getYAccelOffset(),
            getZAccelOffset(),getXGyroOffset(),getYGyroOffset(),getZGyroOffset());
    
    calibrateLoop();
}

void AccelGyroModule::calibrateLoop(){
    while(1){
        if (state==0){
          printf("Reading sensors for first time...\n");
          meansensors();
          state++;
          sleep(1);
        }

        if (state==1) {
          printf("\nCalculating offsets...\n");
          calibration();
          state++;
          sleep(1);
        }

        if (state==2) {
          meansensors();
          printf("\nFINISHED!\n");
          printf("\nSensor readings with offsets: \n"
                  "%d\t%d\t%d\t%d\t%d\t%d\t \n\n",mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz);
          printf("Your offsets:\n"
                  "%d\t%d\t%d\t%d\t%d\t%d\t",ax_offset,ay_offset,az_offset,gx_offset,gy_offset,gz_offset);
          printf("\n\nData is printed as: acelX acelY acelZ giroX giroY giroZ\n");
          printf("Check that your sensor readings are close to 0 0 16384 0 0 0\n");
          printf("If calibration was succesful write down your offsets so you can set them \n"
                  "in your projects using something similar to mpu.setXAccelOffset(youroffset)\n");
        //    while (1);
          return;
        }
    }
}

void AccelGyroModule::meansensors(){
  long i=0,buff_ax=0,buff_ay=0,buff_az=0,buff_gx=0,buff_gy=0,buff_gz=0;

  while (i<(buffersize+101)){
    // read raw accel/gyro measurements from device
    getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    if (i>100 && i<=(buffersize+100)){ //First 100 measures are discarded
      buff_ax=buff_ax+ax;
      buff_ay=buff_ay+ay;
      buff_az=buff_az+az;
      buff_gx=buff_gx+gx;
      buff_gy=buff_gy+gy;
      buff_gz=buff_gz+gz;
    }
    if (i==(buffersize+100)){
      mean_ax=buff_ax/buffersize;
      mean_ay=buff_ay/buffersize;
      mean_az=buff_az/buffersize;
      mean_gx=buff_gx/buffersize;
      mean_gy=buff_gy/buffersize;
      mean_gz=buff_gz/buffersize;
    }
    i++;
    mDelay(2); //Needed so we don't get repeated measures
  }
}

void AccelGyroModule::calibration(){
  ax_offset=-mean_ax/8;
  ay_offset=-mean_ay/8;
  az_offset=(16384-mean_az)/8;

  gx_offset=-mean_gx/4;
  gy_offset=-mean_gy/4;
  gz_offset=-mean_gz/4;
  while (1){
    int ready=0;
    setXAccelOffset(ax_offset);
    setYAccelOffset(ay_offset);
    setZAccelOffset(az_offset);

    setXGyroOffset(gx_offset);
    setYGyroOffset(gy_offset);
    setZGyroOffset(gz_offset);

    meansensors();
//    printf("...\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz);

    if (abs(mean_ax)<=acel_deadzone) ready++;
    else ax_offset=ax_offset-mean_ax/acel_deadzone;

    if (abs(mean_ay)<=acel_deadzone) ready++;
    else ay_offset=ay_offset-mean_ay/acel_deadzone;

    if (abs(16384-mean_az)<=acel_deadzone) ready++;
    else az_offset=az_offset+(16384-mean_az)/acel_deadzone;

    if (abs(mean_gx)<=giro_deadzone) ready++;
    else gx_offset=gx_offset-mean_gx/(giro_deadzone+1);

    if (abs(mean_gy)<=giro_deadzone) ready++;
    else gy_offset=gy_offset-mean_gy/(giro_deadzone+1);

    if (abs(mean_gz)<=giro_deadzone) ready++;
    else gz_offset=gz_offset-mean_gz/(giro_deadzone+1);

    if (ready==6) break;
  }
}

void AccelGyroModule::getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, 
        int16_t* gy, int16_t* gz){
    wBuf[0] = ACCEL_XOUT_H;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,14);
    
    *ax = (((int16_t)rBuf[0]) << 8) | rBuf[1];
    *ay = (((int16_t)rBuf[2]) << 8) | rBuf[3];
    *az = (((int16_t)rBuf[4]) << 8) | rBuf[5];
    *gx = (((int16_t)rBuf[8]) << 8) | rBuf[9];
    *gy = (((int16_t)rBuf[10]) << 8) | rBuf[11];
    *gz = (((int16_t)rBuf[12]) << 8) | rBuf[13];
}

void AccelGyroModule::setXAccelOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_XA_OFFS_H;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}

void AccelGyroModule::setYAccelOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_YA_OFFS_H;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}
void AccelGyroModule::setZAccelOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_ZA_OFFS_H;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}

void AccelGyroModule::setXGyroOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_XG_OFFS_USRH;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}

void AccelGyroModule::setYGyroOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_YG_OFFS_USRH;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}
void AccelGyroModule::setZGyroOffset(uint16_t offset){
    wBuf[0] = MPU6050_RA_ZG_OFFS_USRH;
    wBuf[1] = (uint8_t)(offset >> 8);
    wBuf[2] = (uint8_t)offset;
    bcm2835_i2c_write(wBuf,3);
    
}

int16_t AccelGyroModule::getXAccelOffset(){
    wBuf[0] = MPU6050_RA_XA_OFFS_H;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}

int16_t AccelGyroModule::getYAccelOffset(){
    wBuf[0] = MPU6050_RA_YA_OFFS_H;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}
int16_t AccelGyroModule::getZAccelOffset(){
    wBuf[0] = MPU6050_RA_ZA_OFFS_H;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}

int16_t AccelGyroModule::getXGyroOffset(){
    wBuf[0] = MPU6050_RA_XG_OFFS_USRH;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}

int16_t AccelGyroModule::getYGyroOffset(){
    wBuf[0] = MPU6050_RA_YG_OFFS_USRH;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}
int16_t AccelGyroModule::getZGyroOffset(){
    wBuf[0] = MPU6050_RA_ZG_OFFS_USRH;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,2);
    return (int16_t)((rBuf[0]<<8) | rBuf[1]);    
}

bool AccelGyroModule::testConnection(){
    selectModule();
    wBuf[0] = 0x75;
    bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
    
    return rBuf[0] == 0x68;
}

void AccelGyroModule::getAccelMeas(){
    // - Accel measurements (Burst Read Sequence)
    wBuf[0] = ACCEL_XOUT_H; // - Initial register address
    bcm2835_i2c_write(wBuf, 1);
    result = bcm2835_i2c_read(rBuf, 6); // - 
//    printf("Accel Measurement Status: %d\n",result);
    
    accelMeas.xValue = fullRangeMeas((rBuf[0] << 8) | rBuf[1]);
    accelMeas.yValue = fullRangeMeas((rBuf[2] << 8) | rBuf[3]);
    accelMeas.zValue = fullRangeMeas((rBuf[4] << 8) | rBuf[5]);
//    printf("- AccelX = %d; Scaled: %0.5f => xAngle: %0.5f\n",accelMeas.xValue,
//            accelMeas.xValue/accelScaleFactor,axisAngle(accelMeas.xValue,accelMeas.zValue));
//    printf("- AccelY = %d; Scaled: %0.5f => yAngle: %0.5f\n",accelMeas.yValue,
//            accelMeas.yValue/accelScaleFactor,axisAngle(accelMeas.yValue,accelMeas.zValue));
//    printf("- AccelZ = %d; Scaled: %0.5f\n",accelMeas.zValue,accelMeas.zValue/accelScaleFactor);    
}

/**
 * Obtains the angle of the given axis measurement considering the z-axis measurement as
 * reference.
 * @param meas
 * @param zRef
 * @return: The angle of the given axis in radians, the range is 0 - 2*pi radians
 */
float AccelGyroModule::axisAngle(int accMeas, int zRef){
    // - Angle on x Axis changing positively => CounterClockWise
    // - Cuadrant I and IV
    float radAngle = 0;
    if(zRef >= 0){
        radAngle = atan((float)accMeas/zRef);
//        if(accMeas >= 0) // - Cuadrant I
//            radAngle = atan((float)accMeas/zRef);
//        else // - Cuadrant IV, tan^{-1} returns negative angle
//            radAngle = (2*M_PI + atan((float)accMeas/zRef));
    }else{    // - Cuadrant II and III
        if(accMeas >= 0)
            radAngle = M_PI + atan((float)accMeas/zRef);
        else
            radAngle = -M_PI + atan((float)accMeas/zRef);
    }    
    
    return radAngle*180/M_PI;
}

float AccelGyroModule::getXAngle(){
    return atan(-accelX/ sqrt(accelY*accelY + accelZ*accelZ) )*180/M_PI;
//    return axisAngle(accelMeas.xValue,accelMeas.zValue);
}

float AccelGyroModule::getYAngle(){
    return atan(accelY/accelZ) *180/M_PI;
//    return axisAngle(accelMeas.yValue,accelMeas.zValue);
}

void AccelGyroModule::getGyroMeas(){
    // - Gyro measurements (Burst Read Sequence)
    wBuf[0] = GYRO_XOUT_H; // - Initial register address
    bcm2835_i2c_write(wBuf, 1);
    result = bcm2835_i2c_read(rBuf, 6); // - 
//    printf("Gyro Measurement Status: %d\n",result);
        
    
    gyroMeas.xValue = (int16_t)((rBuf[0] << 8) | rBuf[1]);
    gyroMeas.yValue = (int16_t)((rBuf[2] << 8) | rBuf[3]);
    gyroMeas.zValue = (int16_t)((rBuf[4] << 8) | rBuf[5]);
//    printf("- GyroX = %d; Scaled: %0.5f\n",gyroMeas.xValue,
//            gyroMeas.xValue/gyroScaleFactor);
//    printf("- GyroY = %d; Scaled: %0.5f\n",gyroMeas.yValue,
//            gyroMeas.yValue/gyroScaleFactor);
//    printf("- GyroZ = %d; Scaled: %0.5f\n",gyroMeas.zValue,
//            gyroMeas.zValue/gyroScaleFactor);
}

void AccelGyroModule::getMeas(){
    // - Gyro measurements (Burst Read Sequence)
    wBuf[0] = ACCEL_XOUT_H; // - Initial register address
    bcm2835_i2c_write(wBuf, 1);
    result = bcm2835_i2c_read(rBuf, 14); // - 
//    printf("Gyro Measurement Status: %d\n",result);
        
    accelMeas.xValue = (int16_t)((rBuf[0] << 8) | rBuf[1]);
    accelMeas.yValue = (int16_t)((rBuf[2] << 8) | rBuf[3]);
    accelMeas.zValue = (int16_t)((rBuf[4] << 8) | rBuf[5]);
    accelX = accelMeas.xValue/accelScaleFactor;
    accelY = accelMeas.yValue/accelScaleFactor;
    accelZ = accelMeas.zValue/accelScaleFactor;
    gyroMeas.xValue = (int16_t)((rBuf[8] << 8) | rBuf[9]);
    gyroMeas.yValue = (int16_t)((rBuf[10] << 8) | rBuf[11]);
    gyroMeas.zValue = (int16_t)((rBuf[12] << 8) | rBuf[13]);
//    printf("- GyroX = %d; Scaled: %0.5f\n",gyroMeas.xValue,
//            gyroMeas.xValue/gyroScaleFactor);
//    printf("- GyroY = %d; Scaled: %0.5f\n",gyroMeas.yValue,
//            gyroMeas.yValue/gyroScaleFactor);
//    printf("- GyroZ = %d; Scaled: %0.5f\n",gyroMeas.zValue,
//            gyroMeas.zValue/gyroScaleFactor);
}

float AccelGyroModule::getRoll(){
    return atan2((float)accelMeas.yValue, (float)accelMeas.zValue) * RAD_TO_DEG;
}

float AccelGyroModule::getYGyro(){
    return gyroMeas.yValue/gyroScaleFactor;
}

float AccelGyroModule::getXGyro(){
    return gyroMeas.xValue/gyroScaleFactor;
}

int AccelGyroModule::fullRangeMeas(uint16_t reading){
    if(reading >= 0x8000)
        return -((65535 - reading)+1);
    else
        return (int)reading;
}


//void AccelGyroModule::kalman_yInit(float dt){
//    measnoise = 0.1;
//    accelNoise = 0.1;
//    driftNoise = 0.1;
//    A = {{1.0,-dt},{0.0,1.0}};
//    B = {dt, 0};
//    C = {1.0,0.0};
//    x = {0.0,0.0};
//    y = {0};
//    x_hat = {0.0,0.0};
//    
//    Sz = measnoise*measnoise;
//    Sw = {{dt*accelNoise*accelNoise, 0},{0, dt*driftNoise*driftNoise}};
//    P = {{dt*accelNoise*accelNoise, 0},{0, dt*driftNoise*driftNoise}};
//    
//    // - Plotting DataSet
//    fileName = "yAngleResults.csv";
//    outputFile.open(fileName.c_str(),ios_base::out);
//    if ( ! outputFile.is_open() ){    
//        cout << "El archivo: "+fileName+" no se pudo abrir!!" << '\n';    
//        exit(1);
//    }
//    t = 0;
//    outputFile<<"\"time\",\"measured_angle\",\"estimated_angle\",\"estimated_drift\""<<endl;    
//    
//    // - Stabilization cicle
//    for(uint8_t i = 0; i < 5; i++){
//        kalman_yAngle();
//        usleep((unsigned int)(1000*dt)*1000);
//    }
//}
//
//float AccelGyroModule::kalman_yAngle(){   
//    getAccelMeas();
//    getGyroMeas();
//    y(0) = getYAngle();
//    u = getXW(); // - The vector of the angular velocity for the plane YZ is
//                // - positive on the X axis.
//
//    // - Extrapolate the most recent state estimate to the present time.
//    x_hat = A * x_hat + B * u;
//    // - Form the Innovation vector.
//    Inn = y - C * x_hat;
//    // - Compute the covariance of the Innovation.
//    s = C * P * C.t() + Sz;
//    // - Form the Kalman Gain matrix.
//    K = A * P * C.t() * s.i();
//    // - Update the state estimate.
//    x_hat = x_hat + K * Inn;
//    // - Compute the covariance of the estimation error.
//    P = A * P * A.t() - A * P * C.t() * s.i() * C * P * A.t() + Sw;
//
//    outputFile<<t<<','<<y(0)<<','<<x_hat(0)<<','<<x_hat(1)<<endl;            
//    t++;
//
//    return x_hat(0);
//}