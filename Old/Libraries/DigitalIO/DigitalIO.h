/* 
 * File:   DigitalIO.h
 * Author: yova
 *
 * Created on 21 de mayo de 2016, 01:57 PM
 * 
 * This library is intended for handling digital IO available in the Shield Module.
 * There are 3 digital IOs that have a logic level shifter, so they are compatible
 * with external devices with 5v logic. By external devices we mean devices from 
 * different vendors, which we don't produce for now. These pins are (they are named 
 * according to the BCM2835 library http://www.airspayce.com/mikem/bcm2835/index.html):
 * 
 * {RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_16, RPI_V2_GPIO_P1_17}
 * 
 * The remaining IO pins (the ones with 4pins JST headers) only have a pull-up resistor 
 * with the 3.3v voltage source provided by the RPI, which means that they sould 
 * only be used for connecting Robotois Modules. However, they can still be used 
 * for user applications, but it will require a logic level shifter. If you really 
 * need to use these IO pins for a specific application, please contact Robotois 
 * for more information. These IO pins are:
 * 
 * {RPI_V2_GPIO_P1_29, RPI_V2_GPIO_P1_31, RPI_V2_GPIO_P1_32, RPI_V2_GPIO_P1_33, 
 * RPI_V2_GPIO_P1_35, RPI_V2_GPIO_P1_36, RPI_V2_GPIO_P1_37, RPI_V2_GPIO_P1_38}
 */

#include <bcm2835.h>

#ifndef DIGITALIO_H
#define	DIGITALIO_H

#define AS_INPUT 0x00
#define AS_OUTPUT 0x01

#define IO_HV_1 RPI_V2_GPIO_P1_15 // 5v Logic IO
#define IO_HV_2 RPI_V2_GPIO_P1_16 // 5v Logic IO
#define IO_HV_3 RPI_V2_GPIO_P1_18 // 5v Logic IO

class DigitalIO {
public:
    DigitalIO();
    DigitalIO(uint8_t _io_pin, uint8_t io_direction);
//    DigitalIO(uint8_t _io_header,uint8_t io1_dir,uint8_t io2_dir);
    DigitalIO(const DigitalIO& orig);
    virtual ~DigitalIO();
    
    void write(uint8_t state);

    void riseEventEnable();
    bool riseEventDetected();
    void fallEventEnable();
    bool fallEventDetected();
private:
    uint8_t io_pin;
    void setAsOutput();
    void setAsInput();
};

#endif	/* DIGITALIO_H */

