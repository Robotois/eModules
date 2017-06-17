/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PHSensor.h
 * Author: yovany
 *
 * Created on January 20, 2017, 5:59 PM
 */

#ifndef PHSENSOR_H
#define PHSENSOR_H
#include"../../Libraries/ADS1015/ADS1015.h"

class PHSensor {
public:
    PHSensor(uint8_t _add = 0x00);
    PHSensor(const PHSensor& orig);
    virtual ~PHSensor();
    
    void selectPort(uint8_t _port);
    float read();
    float readRaw();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;
    float scaleFactor,slope;
    
};

#endif /* PHSENSOR_H */

