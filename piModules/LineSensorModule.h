/* 
 * File:   LineFinder.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 12:47 PM
 */
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include <bcm2835.h>

#ifndef LINESENSORMODULE_H
#define	LINESENSORMODULE_H


class LineSensorModule {
public:
    uint8_t slave_address;

    LineSensorModule();
    LineSensorModule(const LineSensorModule& orig);
    virtual ~LineSensorModule();
    
    // - Establecer Configuracion
    void initialize();
    void selectModule();
    uint8_t getInputs();
    float readLine();
private:
    static const uint8_t IODIR = 0x00,   // - IO direction
            IPOL = 0x01,    // - Input polatity
            GPPU = 0x06,    // - Pull-up register
            GPIO = 0x09;    // - IO Port
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length

};

#endif	/* LINEFINDER_H */

