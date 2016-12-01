/* 
 * File:   Button.h
 * Author: yova
 *
 * Created on 8 de septiembre de 2016, 06:04 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <bcm2835.h>
#include "../../Libraries/DigitalIO/DigitalHeader.h"

class Button {
public:
    Button(uint8_t header);
    Button(const Button& orig);
    virtual ~Button();
    
    uint8_t read();
private:
    DigitalHeader *IOHeader;
    uint8_t state;

};

#endif	/* BUTTON_H */

