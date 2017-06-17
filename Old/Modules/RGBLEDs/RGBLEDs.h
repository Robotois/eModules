/* 
 * File:   RGBLEDs.h
 * Author: yova
 *
 * Created on 27 de mayo de 2016, 08:38 AM
 */

#ifndef RGBLEDS_H
#define	RGBLEDS_H

#include "../../Libraries/PCA9685/PCA9685.h"

#define RGBLEDs_ADDRESS 0x04 // - Default Address

class RGBLEDs {
public:
    RGBLEDs(uint8_t _addr = 0x00);
    RGBLEDs(const RGBLEDs& orig);
    virtual ~RGBLEDs();
    
    void setRGB(uint8_t _led_number,uint8_t _red_code,uint8_t _green_code,uint8_t _blue_code);
    void blinkRGB(uint8_t _led_number,uint8_t _red_code,uint8_t _green_code,uint8_t _blue_code);
    void ledOff(uint8_t _led_number);
    void allOff();
    void allOn(uint8_t _red_code,uint8_t _green_code,uint8_t _blue_code);
    
    void release();
private:
    float pwmRatio;
    PCA9685 *pwmModule;
    uint16_t *rgbCode;
    
    bool powerOn;

};

#endif	/* RGBLEDS_H */

