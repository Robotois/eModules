/* 
 * File:   OpticalDistanceSensor.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 09:06 AM
 */


#ifndef OPTICALDISTANCESENSOR_H
#define	OPTICALDISTANCESENSOR_H

#include "../../Libraries/ADS1015/ADS1015.h"

class OpticalDistanceSensor {
public:
    OpticalDistanceSensor(uint8_t _addr = 0x00);
    OpticalDistanceSensor(const OpticalDistanceSensor& orig);
    virtual ~OpticalDistanceSensor();
    
    void selectPort(uint8_t _addr);
    float getDistance();
private:
    ADS1015 *analogModule;
    uint8_t inputPort;

};

#endif	/* OPTICALDISTANCESENSOR_H */

