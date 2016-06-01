/* 
 * File:   OpticalDistanceSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 09:06 AM
 */

#include "../../Libraries/ADS1015/ADS1015.h"

#ifndef OPTICALDISTANCESENSOR_H
#define	OPTICALDISTANCESENSOR_H

class OpticalDistanceSensor {
public:
    OpticalDistanceSensor(uint8_t _addr = 0x48);
    OpticalDistanceSensor(const OpticalDistanceSensor& orig);
    virtual ~OpticalDistanceSensor();
    
    void selectPort(uint8_t _addr);
    float getDistance();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;

};

#endif	/* OPTICALDISTANCESENSOR_H */

