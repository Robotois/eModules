/* 
 * File:   UltrasonicSensor.h
 * Author: yova
 *
 * Created on 16 de abril de 2016, 06:17 PM
 */

#include <bcm2835.h>
#include "../../Modules/DigitalIO/DigitalHeader.h"

#ifndef ULTRASONICSENSOR_H
#define	ULTRASONICSENSOR_H

using namespace std;

class UltrasonicSensor {
public:
    UltrasonicSensor();
    UltrasonicSensor(uint8_t header);
    UltrasonicSensor(const UltrasonicSensor& orig);
    virtual ~UltrasonicSensor();
    
    double getDistance();
    void initialize(uint8_t header);
    
    bool connectionTest();

private:
    DigitalHeader *IOHeader;
    uint8_t triggerPin, echoPin;
    
    float measure(uint8_t samples);
    unsigned int readSensor();
    void sendTrigger();
    unsigned int readEcho();
};

#endif	/* ULTRASONICSENSOR_H */

