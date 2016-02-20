/* 
 * File:   Servos.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>

#ifndef SERVOMODULE_H
#define	SERVOMODULE_H

using namespace std;

class ServoModule {
public:
    ServoModule();
    ServoModule(const ServoModule& orig);
    virtual ~ServoModule();
    
    void selectModule();
    void initialize();
    void servoAngle(uint8_t servoNumber,float degree);
private:
    // - Register Addresses
    static const uint8_t MODE1 = 0x00,   // - MODE1 register
            MODE2 = 0x02,    // - MODE2 register
            PRE_SCALE = 0xFE,
            
            ALL_SERVOs_ON_L = 0xFA,
            ALL_SERVOs_ON_H = 0xFB,
            ALL_SERVOs_OFF_L = 0xFC,
            ALL_SERVOs_OFF_H = 0xFD,
            
            SERVO0_ON_L = 0x06,
            SERVO0_ON_H = 0x07,
            SERVO0_OFF_L = 0x08,
            SERVO0_OFF_H = 0x09
    ;
    // - Configuracion de tiempos, 800->2200 usec
    static const uint16_t delay = 410,minOnTime = 164,maxOnTime = 450;
    // - Variables para almacenar los tiempos ON/OFF actuales.
    uint16_t onTime, offTime,maxOffTime,centerOffTime;
    float angleTimeRatio;
    uint8_t slave_address,result;
    // - Buffers de lectura/escritura
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length

};

#endif	/* SERVOS_H */

