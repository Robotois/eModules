/* 
 * File:   LineFinder.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 12:47 PM
 */
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include "../../Libraries/MCP23008/MCP23008.h"
//#include <bcm2835.h>

#ifndef LINESENSORS_H
#define	LINESENSORS_H

#define LINESENSORS_SENSOR1 0x00
#define LINESENSORS_SENSOR2 0x01
#define LINESENSORS_SENSOR3 0x02
#define LINESENSORS_SENSOR4 0x03
#define LINESENSORS_SENSOR5 0x04
#define LINESENSORS_SENSOR6 0x05
#define LINESENSORS_ENABLE 0x06

#define LINESENSORS_BLACK_BACKGROUND 0x01
#define LINESENSORS_WHITE_BACKGROUND 0x00

class LineSensors {
public:
//    uint8_t slave_address;

    LineSensors(uint8_t _addr = 0x00);
    LineSensors(const LineSensors& orig);
    virtual ~LineSensors();
    
    // - Establecer Configuracion
//    void selectModule();
    uint8_t  readSensors();
    float readLine();
    void setBackground(uint8_t _bg);
    uint8_t readSensor(uint8_t _sensor);
private:
    MCP23008 *mcp;
    uint8_t _io_pins[8], background;
    void initialize();
//    static const uint8_t IODIR = 0x00,   // - IO direction
//            IPOL = 0x01,    // - Input polatity
//            GPPU = 0x06,    // - Pull-up register
//            GPIO = 0x09;    // - IO Port
//    char rBuf[10]; // - Max length
//    char wBuf[10]; // - Max length

};

#endif	/* LINEFINDER_H */

