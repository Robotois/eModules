/* 
 * File:   LightSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 01:52 PM
 */

#include"../../Libraries/ADS1015/ADS1015.h"

#ifndef LIGHTSENSOR_H
#define	LIGHTSENSOR_H

class LightSensor {
public:    
    LightSensor(uint8_t _addr = 0x48);
    LightSensor(const LightSensor& orig);
    virtual ~LightSensor();
    
    void selectPort(uint8_t _port);
    float getLight();
    int16_t getScaledLight();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;
    float scaleFactor;

};

#endif	/* LIGHTSENSOR_H */

