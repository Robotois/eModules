/* 
 * File:   BCMSetup.cpp
 * Author: yova
 * 
 * Created on 7 de junio de 2016, 10:27 PM
 */

#include <bcm2835.h>
#include<iostream>

#include "BCMSetup.h"

BCMSetup::BCMSetup() {
}

BCMSetup::BCMSetup(const BCMSetup& orig) {
}

BCMSetup::~BCMSetup() {
    bcm_end();
}

uint8_t BCMSetup::bcm_init(){
    // - 400kHz aproximadamente...
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_626;

    // - Slave address is set by each module
    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        return 0x00;
//        exit(1);
    }
    
    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
    
    return 0x01;
}

void BCMSetup::bcm_end(){
    bcm2835_i2c_end();
    bcm2835_close();    
}

void BCMSetup::set_slave(uint8_t _addr){
//    bcm_init();
    bcm2835_i2c_setSlaveAddress(_addr);
//    printf("Slave Set Add: %d...\n",_addr);
}

uint8_t BCMSetup::read_register(char* regAddr, char* buf,uint16_t len){
    return bcm2835_i2c_read_register_rs(regAddr,buf,len);
}

uint8_t BCMSetup::write(char* buf, uint16_t len){
    return bcm2835_i2c_write(buf, len);
}

