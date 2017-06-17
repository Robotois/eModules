/* 
 * File:   TempSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 03:33 PM
 */

#ifndef TEMPERATURESENSOR_H
#define	TEMPERATURESENSOR_H

#include <stdlib.h>

#include "../../Libraries/ADS1015/ADS1015.h"

class TemperatureSensor {
public:
    TemperatureSensor(uint8_t _addr = 0x00);
    TemperatureSensor(const TemperatureSensor& orig);
    virtual ~TemperatureSensor();
    
    void selectPort(uint8_t _port);
    float getValue();
//    float getBasicValue();
    int16_t getIntValue();
    
    void release();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;    
    float tempRatio;
};

#endif	/* TEMPSENSOR_H */

