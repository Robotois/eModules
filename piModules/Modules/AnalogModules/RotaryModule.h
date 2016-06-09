/* 
 * File:   RotaryModule.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 04:10 PM
 */

#ifndef ROTARYMODULE_H
#define	ROTARYMODULE_H

#include"../../Libraries/ADS1015/ADS1015.h"

class RotaryModule {
public:
    RotaryModule(uint8_t _addr = 0x00);
    RotaryModule(const RotaryModule& orig);
    virtual ~RotaryModule();
    
    void selectPort(uint8_t _port);
    float getValue();
    int16_t getScaledValue();    
private:
    ADS1015 *analogModule;
    uint8_t inputPort;
    float scaleFactor;

};

#endif	/* ROTARYMODULE_H */

