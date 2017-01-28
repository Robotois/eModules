/* 
 * File:   RotarySensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 04:10 PM
 */

#ifndef ROTARYSENSOR_H
#define	ROTARYSENSOR_H

#include"../../Libraries/ADS1015/ADS1015.h"

class RotarySensor {
public:
    RotarySensor(uint8_t _addr = 0x00);
    RotarySensor(const RotarySensor& orig);
    virtual ~RotarySensor();
    
    void selectPort(uint8_t _port);
    float getValue();
//    float getBasicValue();
    int16_t getScaledValue();    
    int16_t getBasicScaledValue();    
    
    void release();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;
    float scaleFactor, basicScaleFactor;

};

#endif	/* ROTARYMODULE_H */

