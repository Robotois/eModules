/* 
 * File:   LightSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 01:52 PM
 */

#ifndef LIGHTSENSOR_H
#define	LIGHTSENSOR_H
#include"../../Libraries/ADS1015/ADS1015.h"

class LightSensor {
public:    
    LightSensor(uint8_t _addr = 0x00);
    LightSensor(const LightSensor& orig);
    virtual ~LightSensor();
    
    void selectPort(uint8_t _port);
    float getValue();
//    float getBasicValue();
    int16_t getScaledValue();    
    int16_t getBasicScaledValue();    
private:
    ADS1015 *analogModule;
    uint8_t inputPort;
    float scaleFactor,basicScaleFactor;

};

#endif	/* LIGHTSENSOR_H */

