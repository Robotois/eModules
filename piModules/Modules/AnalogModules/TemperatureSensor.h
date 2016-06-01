/* 
 * File:   TempSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 03:33 PM
 */

#include "../../Libraries/ADS1015/ADS1015.h"

#ifndef TEMPERATURESENSOR_H
#define	TEMPERATURESENSOR_H

class TemperatureSensor {
public:
    TemperatureSensor(uint8_t _addr = 0x48);
    TemperatureSensor(const TemperatureSensor& orig);
    virtual ~TemperatureSensor();
    
    void selectPort(uint8_t _port);
    float getTemperature();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;    
};

#endif	/* TEMPSENSOR_H */

