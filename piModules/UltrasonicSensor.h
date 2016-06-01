/* 
 * File:   UltrasonicSensor.h
 * Author: yova
 *
 * Created on 16 de abril de 2016, 06:17 PM
 */

#include <bcm2835.h>
//#include "Modules/DigitalIO/DigitalIO.h"
#include "Modules/DigitalIO/DigitalHeader.h"

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
//    void initialize();

private:
//    typedef std::chrono::high_resolution_clock::time_point ClockTiming;
    DigitalHeader *IOHeader;
    uint8_t triggerPin, echoPin;
//    std::chrono::high_resolution_clock::time_point startTime, elapsedTime;
    
    void setPins(int _triggerPin, int _echoPin);
    double measure(int samples);
    long int readSensor();
    void sendTrigger();
    unsigned int readEcho();
    long int echoLength(long int start_time);
//    void nsleep(long us);
};

#endif	/* ULTRASONICSENSOR_H */

