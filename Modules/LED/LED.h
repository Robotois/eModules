/* 
 * File:   LED.h
 * Author: yova
 *
 * Created on 8 de septiembre de 2016, 05:48 PM
 */

#ifndef LED_H
#define	LED_H

#include <bcm2835.h>
#include "../../Libraries/DigitalIO/DigitalHeader.h"

class LED {
public:
//    LED();
    LED(uint8_t _header);
    LED(const LED& orig);
    virtual ~LED();
    
    void write(uint8_t state);
private:
    DigitalHeader *IOHeader;
};

#endif	/* LED_H */

