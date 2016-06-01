/* 
 * File:   Servos.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */

//#include <cstdlib>
//#include <stdio.h>
//#include <unistd.h>
//#include <bcm2835.h>

#include "../../Libraries/PCA9685/PCA9685.h"

#ifndef SERVOS_H
#define	SERVOS_H

using namespace std;

class Servos {
public:
    Servos(uint8_t _addr = 0x00);
    Servos(const Servos& orig);
    virtual ~Servos();
    
    void initialize();
    void setAngle(uint8_t servoNumber,float degree);
private:
    float minTravel, maxTravel;
    // - Configuracion de tiempos, 800->2200 usec => 165 degrees
//    static const uint16_t minOnTime = 164,maxOnTime = 450;
    // - Configuracion de tiempos, 700->2300 usec => 180 degrees
    static const uint16_t minOnTime = 143,maxOnTime = 471;
    // - Variables para almacenar los tiempos ON/OFF actuales.
    uint16_t onTime, offTime,maxOffTime,halfOffTime,centerOffTime;
    float angleTimeRatio;
//    uint8_t slave_address,result;
    // - Buffers de lectura/escritura
//    char rBuf[10]; // - Max length
//    char wBuf[10]; // - Max length
    
    PCA9685 *pwmModule;

};

#endif	/* SERVOS_H */

