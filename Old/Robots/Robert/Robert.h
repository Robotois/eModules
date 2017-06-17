/* 
 * File:   Robert.h
 * Author: yova
 *
 * Created on 19 de abril de 2016, 01:21 PM
 */

#ifndef ROBERT_H
#define	ROBERT_H

#include "../../Modules/Motors/Motors.h"

#include "../../Modules/Ultrasonic/UltrasonicSensor.h"
#include "../../Modules/Servos/Servos.h"
#include "../../Modules/LineSensors/LineSensors.h"

class Robert {
public:
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
    Motors *motorModule;
    UltrasonicSensor *ultrasonicSensor;
    LineSensors *lineModule;
private:
    Servos *servos;
    void constrain(float* value, float min, float max);

};

#endif	/* ROBERT_H */

