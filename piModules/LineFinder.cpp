/* 
 * File:   LineFinder.cpp
 * Author: yova
 * 
 * Created on 28 de enero de 2016, 01:48 PM
 */

#include <math.h>
#include "LineFinder.h"

LineFinder::LineFinder() {
    // - default
    L = 90+15; // - Distancia en [mm] del eje de los motores al modulo de sensores.
}

LineFinder::LineFinder(double _L,double _wheelRadius,double _motorDist){
    L = _L+15; // - Distancia en [mm] del eje de los motores al modulo de sensores.
    wheelPerim = 2*M_PI*_wheelRadius;
    motorDist = _motorDist;
}

LineFinder::LineFinder(const LineFinder& orig) {
}

LineFinder::~LineFinder() {
}

void LineFinder::setSpeed(double _speed){
    speed = _speed;
}

void LineFinder::curveMeasurements(uint8_t sensorInputs){
    double Ls;
    switch(sensorInputs){
        // - [1 0 0 0 0 0], [1 1 0 0 0 0]
        case 0x01:
        case 0x03:
            Ls = 23.8125;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("Ls: %0.5f => Alpha: %0.5f\n",Ls,alpha);
            iccSide = 1;
            break;
        // - [0 1 0 0 0 0], [0 1 1 0 0 0]
        case 0x02:
        case 0x06:
            Ls = 14.2875;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("Ls: %0.5f => Alpha: %0.5f\n",Ls,alpha);
            iccSide = 1;
            break;                
        // - [0 0 1 0 0 0]
        case 0x04:
            Ls = 4.7625;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("Ls: %0.5f => Alpha: %0.5f\n",Ls,alpha);
            iccSide = 1;
            break;
            
        // - [0 0 1 1 0 0]
        case 0x0C:
            Ls = 0;
            triangBase = L;
            alpha = 0;
//            printf("Ls: %0.5f => Alpha: 0\n",Ls);
            iccSide = 0;
            break;

        // - [0 0 0 1 0 0]
        case 0x08:
            Ls = 4.7625;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("-Ls: %0.5f => -Alpha: %0.5f\n",Ls,alpha);
            iccSide = 2;
            break;
        // - [0 0 0 0 1 0], [0 0 0 1 1 0]
        case 0x10:
        case 0x18:
            Ls = 14.2875;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("-Ls: %0.5f => -Alpha: %0.5f\n",Ls,alpha);
            iccSide = 2;
            break;                
        // - [0 0 0 0 0 1], [0 0 0 0 1 1]
        case 0x20:
        case 0x30:
            Ls = 23.8125;
            triangBase = sqrt(Ls*Ls + L*L);
            alpha = atan(Ls/L);
//            printf("-Ls: %0.5f => -Alpha: %0.5f\n",Ls,alpha);
            iccSide = 2;
            break;

        default:
            Ls = 0;
            triangBase = L;
            alpha = atan(Ls/L);
            iccSide = 0;
//            printf("-Ls: %0.5f => -Alpha: %0.5f\n",Ls,alpha);
//            break;                
    }    

//    printf("iccSide: %d, Ls: %0.5f => Alpha: %0.5f, triangBase: %0.5f\n",iccSide,Ls,alpha,triangBase);
    
    if(iccSide == 0){
        radius = -1;
    }else{
        double phi = M_PI/2-alpha; // - 90°-alpha
        radius = (triangBase/2)/cos(phi);
//        printf("R: %0.6f\n",radius);
        angSpeed = speed/radius;
    }
}

uint16_t LineFinder::leftRPMSpeed(){
    double _speed;
    if(iccSide == 0){
        return speed;
    }
    
    if(iccSide == 1){
        _speed = angSpeed*(radius-motorDist/2);
        return rpmSpeed(_speed);
    }

    if(iccSide == 2){
        _speed = angSpeed*(radius+motorDist/2);
        return rpmSpeed(_speed);
    }
}

uint16_t LineFinder::rightRPMSpeed(){
    double _speed;
    if(iccSide == 0){
        return speed;
    }
    
    if(iccSide == 1){
        _speed = angSpeed*(radius+motorDist/2);
        return rpmSpeed(_speed);
    }

    if(iccSide == 2){
        _speed = angSpeed*(radius-motorDist/2);
        return rpmSpeed(_speed);
    }
}

uint16_t LineFinder::rpmSpeed(double speed){
    return (speed/wheelPerim)*60;
}