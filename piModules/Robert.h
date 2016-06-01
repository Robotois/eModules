/* 
 * File:   Robert.h
 * Author: yova
 *
 * Created on 19 de abril de 2016, 01:21 PM
 */

#ifndef ROBERT_H
#define	ROBERT_H

#include "Motors.h"

#include "UltrasonicSensor.h"
#include "ServoModule.h"

class Robert {
public:
    Motors *motorModule;
    UltrasonicSensor *ultrasonicSensor;
    ServoModule *servos;
    Robert();
    Robert(const Robert& orig);
    virtual ~Robert();
    
    void LineFollower();
    void MazeSolver();
    
    void turnRight();
    void turnLeft();
    void turnAround();
    void moveForward();
    void moveForward(uint16_t maSpeed,uint16_t mbSpeed);
    void stop();
    void moveBackward();
    
    void lookLeft();
    void lookRight();
    double leftDistance();
    double rightDistance();
    double frontDistance();
    
    void estimateDirection();
private:

};

#endif	/* ROBERT_H */

