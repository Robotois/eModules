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
#define DIGITAL_HEADER1_1 RPI_V2_GPIO_P1_12 // 3.3v Logic IO
#define DIGITAL_HEADER1_2 RPI_V2_GPIO_P1_13 // 3.3v Logic IO
#define DIGITAL_HEADER2 0x02
#define DIGITAL_HEADER2_1 RPI_V2_GPIO_P1_15 // 3.3v Logic IO
#define DIGITAL_HEADER2_2 RPI_V2_GPIO_P1_16 // 3.3v Logic IO
#define DIGITAL_HEADER3 0x03
#define DIGITAL_HEADER3_1 RPI_V2_GPIO_P1_18 // 3.3v Logic IO
#define DIGITAL_HEADER3_2 RPI_V2_GPIO_P1_19 // 3.3v Logic IO
#define DIGITAL_HEADER4 0x04
#define DIGITAL_HEADER4_1 RPI_V2_GPIO_P1_21 // 3.3v Logic IO
#define DIGITAL_HEADER4_2 RPI_V2_GPIO_P1_22 // 3.3v Logic IO
#define DIGITAL_HEADER5 0x05
#define DIGITAL_HEADER5_1 RPI_V2_GPIO_P1_23 // 3.3v Logic IO
#define DIGITAL_HEADER5_2 RPI_V2_GPIO_P1_24 // 3.3v Logic IO
#define DIGITAL_HEADER6 0x06
#define DIGITAL_HEADER6_1 RPI_V2_GPIO_P1_29 // 3.3v Logic IO
#define DIGITAL_HEADER6_2 RPI_V2_GPIO_P1_31 // 3.3v Logic IO

class DigitalHeader {
public:
    uint8_t io_pin1,io_pin2, io1_dir,io2_dir;
    DigitalHeader();
    DigitalHeader(uint8_t _io_header,uint8_t io1_dir,uint8_t io2_dir);
    DigitalHeader(const DigitalHeader& orig);
    virtual ~DigitalHeader();

    void io1_asInput();    
    void io1_asOutput();
    void io1_write(uint8_t state);    
    uint8_t io1_read();    
    void io1_riseEnable();
    bool io1_riseDetected();
    void io1_fallEnable();
    bool io1_fallDetected();
    
    void io2_asInput();
    void io2_asOutput();
    void io2_write(uint8_t state);    
    uint8_t io2_read();    
    void io2_riseEnable();
    bool io2_riseDetected();
    void io2_fallEnable();
    bool io2_fallDetected();
    
    void release();
private:
    
    void asOutput(uint8_t io_pin);
    void asInput(uint8_t io_pin);

    void write(uint8_t io_pin,uint8_t state);
    uint8_t read(uint8_t io_pin);

    void riseEnable(uint8_t io_pin);
    bool riseDetected(uint8_t io_pin);
    void fallEnable(uint8_t io_pin);
    bool fallDetected(uint8_t io_pin);

    void bcm_init();
    void bcm_end();

};

#endif	/* DIGITALHEADER_H */

