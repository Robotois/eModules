/* 
 * File:   RGBLEDs.h
 * Author: yova
 *
 * Created on 27 de mayo de 2016, 08:38 AM
 */

#include "../../Libraries/PCA9685/PCA9685.h"
#ifndef RGBLEDS_H
#define	RGBLEDS_H

class RGBLEDs {
public:
    RGBLEDs(uint8_t _add = 0x01);
    RGBLEDs(const RGBLEDs& orig);
    virtual ~RGBLEDs();
    
    void setRGB(uint8_t _led_number,uint8_t _red_code,uint8_t _green_code,uint8_t _blue_code);
private:
    float pwmRatio;
    PCA9685 *pwmModule;
    uint16_t *rgbCode;

};

#endif	/* RGBLEDS_H */

