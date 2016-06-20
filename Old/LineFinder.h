/* 
 * File:   LineFinder.h
 * Author: yova
 *
 * Created on 28 de enero de 2016, 01:48 PM
 */
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>

#ifndef LINEFINDER_H
#define	LINEFINDER_H

class LineFinder {
public:
    LineFinder();
    LineFinder(double _L,double _wheelRadius,double _motorDist);
    LineFinder(const LineFinder& orig);
    virtual ~LineFinder();
    
    void curveMeasurements(uint8_t sensorInputs);
    void setSpeed(double _speed);
    uint16_t leftRPMSpeed();
    uint16_t rightRPMSpeed();
    uint16_t rpmSpeed(double speed);
private:
    double L,triangBase,alpha,radius,wheelPerim,speed,angSpeed,motorDist;
    uint8_t iccSide;

};

#endif	/* LINEFINDER_H */

