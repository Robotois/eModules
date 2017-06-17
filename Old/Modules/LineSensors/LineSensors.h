/* 
 * File:   LineFinder.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 12:47 PM
 */

#ifndef LINESENSORS_H
#define	LINESENSORS_H

#include "../../Libraries/MCP23008/MCP23008.h"

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
    LineSensors(uint8_t _addr = 0x00);
    LineSensors(const LineSensors& orig);
    virtual ~LineSensors();
    
    // - Establecer Configuracion
    uint8_t  readSensors();
    int16_t readLine();
    void setBackground(uint8_t _bg);
    uint8_t readSensor(uint8_t _sensor);
private:
    MCP23008 *mcp;
    uint8_t _io_pins[8], background;
    void initialize();
};

#endif

