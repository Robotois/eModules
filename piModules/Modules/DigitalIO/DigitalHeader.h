/* 
 * File:   DigitalHeader.h
 * Author: yova
 *
 * Created on 25 de mayo de 2016, 12:25 PM
 */
#include <bcm2835.h>

#ifndef DIGITALHEADER_H
#define	DIGITALHEADER_H

#define AS_INPUT 0x00 //- Indicates that the IO is an Input
#define AS_OUTPUT 0x01 //- Indicates that the IO is an Output

/**
 * 3.3v logic IOs, DH => Digital Header
 */
#define DIGITAL_HEADER1 0x01
#define DIGITAL_HEADER1_1 RPI_V2_GPIO_P1_31 // 3.3v Logic IO
#define DIGITAL_HEADER1_2 RPI_V2_GPIO_P1_29 // 3.3v Logic IO
#define DIGITAL_HEADER2 0x02
#define DIGITAL_HEADER2_1 RPI_V2_GPIO_P1_33 // 3.3v Logic IO
#define DIGITAL_HEADER2_2 RPI_V2_GPIO_P1_32 // 3.3v Logic IO
#define DIGITAL_HEADER3 0x03
#define DIGITAL_HEADER3_1 RPI_V2_GPIO_P1_35 // 3.3v Logic IO
#define DIGITAL_HEADER3_2 RPI_V2_GPIO_P1_36 // 3.3v Logic IO
#define DIGITAL_HEADER4 0x04
#define DIGITAL_HEADER4_1 RPI_V2_GPIO_P1_37 // 3.3v Logic IO
#define DIGITAL_HEADER4_2 RPI_V2_GPIO_P1_38 // 3.3v Logic IO

class DigitalHeader {
public:
    uint8_t io_pin1,io_pin2;
    DigitalHeader();
    DigitalHeader(uint8_t _io_header,uint8_t io1_dir,uint8_t io2_dir);
    DigitalHeader(const DigitalHeader& orig);
    virtual ~DigitalHeader();

    void write(uint8_t io_pin,uint8_t state);
    uint8_t read(uint8_t io_pin);

    void riseEnable(uint8_t io_pin);
    bool riseDetected(uint8_t io_pin);
    void fallEnable(uint8_t io_pin);
    bool fallDetected(uint8_t io_pin);

    void asOutput(uint8_t io_pin);
    void asInput(uint8_t io_pin);
private:


};

#endif	/* DIGITALHEADER_H */

