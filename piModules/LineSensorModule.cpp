/* 
 * File:   LineFinder.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 12:47 PM
 */

#include<bitset>
#include "LineSensorModule.h"

LineSensorModule::LineSensorModule() {
    slave_address = 0x20;   // - Default Address
}

LineSensorModule::LineSensorModule(const LineSensorModule& orig) {
}

LineSensorModule::~LineSensorModule() {
}

/**
 * Reestablece la direccion del esclavo en el puerto i2c. Se debe llamar antes de
 * iniciar una transaccion o serie de transacciones hacia el modulo LineFinder.
 */
void LineSensorModule::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_address);
}

void LineSensorModule::initialize(){
    selectModule();
    // - Configure IO ports
    wBuf[0] = IODIR; // - Access the direction register
    // - IO conf, first 6 ports as inputs, 7th port as output is the enable
    // - pin
    wBuf[1] = 0xBF;
    
    bcm2835_i2c_write(wBuf, 2);

    // - Configure pull-up reistors
    wBuf[0] = GPPU; // - Acess the Pull-up register
    wBuf[1] = 0xBF; // - Pull-ups on every input
    
    bcm2835_i2c_write(wBuf, 2);
    
    // - Enable the sensors
    wBuf[0] = GPIO; // - Access the IO register
    wBuf[1] = 0x40; // - Set the enable output to high.
    
    bcm2835_i2c_write(wBuf, 2);
}

uint8_t LineSensorModule::getInputs(){
    // - Access GPIO.
    wBuf[0] = GPIO; // - Access the IO register
    bcm2835_i2c_write(wBuf, 1);

    // - Read GPIO
    bcm2835_i2c_read(rBuf, 1);
    return rBuf[0]&0x3F;
}

float LineSensorModule::readLine(){
//    typedef std::bitset<sizeof(unsigned char)> IntBits;
//    bool is_set = IntBits(200).test(5);
    uint8_t inputs = getInputs();
    
    if(inputs == 0x00)
        return 0.0;
    
    int cumSum = 0;
    float avg = 0;
    
    for(uint8_t i = 0; i < 6; i++){
        if(inputs & (1<<i)){
            avg += 100 * ((i+1)*100);
            cumSum += 100;
        }
    }
    avg = avg/cumSum;
//    printf("%0.2f\n",avg);
    return avg;
}
