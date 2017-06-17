/* 
 * File:   RGBLEDs.cpp
 * Author: yova
 * 
 * Created on 27 de mayo de 2016, 08:38 AM
 */

#include <stdint.h>
#include <stdlib.h>
#include<iostream>
#include "RGBLEDs.h"

#include "../../Libraries/Timer/AccurateTiming.h"

RGBLEDs::RGBLEDs(uint8_t _addr) {
    if(_addr > 3){ // - 2 bits for custom address
        printf("Wrong slave address for the RGB LEDs Module...\n");
        return;    
    }
    
    pwmModule = new PCA9685(RGBLEDs_ADDRESS | _addr);
    
    pwmModule->setPreScale(0x28); // Prescaler for 150Hz frequency
    pwmModule->setInvertedMode();
    
    pwmModule->allOff();
    
    pwmModule->setOn(15);
    powerOn = true;

    pwmRatio = 4095.0f/(1.5f*255.0f); // Using only a 3rd of the LEDs full brightness
    rgbCode = new uint16_t[3*4]; // 4 LEDs max
}

RGBLEDs::RGBLEDs(const RGBLEDs& orig) {
}

RGBLEDs::~RGBLEDs() {
}

void RGBLEDs::setRGB(uint8_t _led_number, uint8_t _red_code, uint8_t _green_code, uint8_t _blue_code){
    if(_led_number < 1 or _led_number > 4){
        printf("Wrong LED selection...\n");
        return;
//        return;
    }

    if(!powerOn){
        pwmModule->setOn(15);
        powerOn = true;
    }
    rgbCode[0] = (uint16_t)(_blue_code*pwmRatio);
    rgbCode[1] = (uint16_t)(_green_code*pwmRatio);
    rgbCode[2] = (uint16_t)(_red_code*pwmRatio);
    pwmModule->setPWM((uint8_t)((_led_number - 1)*3),(uint8_t)3,rgbCode);
}

void RGBLEDs::blinkRGB(uint8_t _led_number, uint8_t _red_code, uint8_t _green_code, uint8_t _blue_code){
    if(_led_number < 1 or _led_number > 3){
        printf("Wrong LED selection...\n");
        return;
//        return;
    }
    if(!powerOn){
        pwmModule->setOn(15);
        powerOn = true;
    }
//    if(leds_status[_led_number-1] == 0x00){
        rgbCode[0] = (uint16_t)(_blue_code*pwmRatio);
        rgbCode[1] = (uint16_t)(_green_code*pwmRatio);
        rgbCode[2] = (uint16_t)(_red_code*pwmRatio);
        pwmModule->setPWM((uint8_t)((_led_number - 1)*3),(uint8_t)3,rgbCode);
        mDelay(1000);
        ledOff(_led_number);
//        leds_status[_led_number-1] = 0x01;
//    }else{
//        ledOff(_led_number);
//        leds_status[_led_number-1] = 0x00;
//    }
}

void RGBLEDs::ledOff(uint8_t _led_number){
    if(_led_number < 1 or _led_number > 3){
        printf("Wrong LED selection...\n");
        return;
//        return;
    }
    rgbCode[0] = 0x00;
    rgbCode[1] = 0x00;
    rgbCode[2] = 0x00;
    pwmModule->setPWM((uint8_t)((_led_number - 1)*3),(uint8_t)3,rgbCode);
}

void RGBLEDs::release(){
    pwmModule->allOff();    
    pwmModule->release();
    delete pwmModule;
    delete rgbCode;
    powerOn = false;
    
    printf("[RGBModule] => Released\n");
}

void RGBLEDs::allOff(){
    pwmModule->allOff();
    powerOn = false;
}

void RGBLEDs::allOn(uint8_t _red_code,uint8_t _green_code,uint8_t _blue_code){
    if(!powerOn){
        pwmModule->setOn(15);
        powerOn = true;
    }

    rgbCode[0] = _red_code;
    rgbCode[1] = _green_code;
    rgbCode[2] = _blue_code;
    rgbCode[3] = _red_code;
    rgbCode[4] = _green_code;
    rgbCode[5] = _blue_code;
    rgbCode[6] = _red_code;
    rgbCode[7] = _green_code;
    rgbCode[8] = _blue_code;
    rgbCode[9] = _red_code;
    rgbCode[10] = _green_code;
    rgbCode[11] = _blue_code;
    pwmModule->setPWM((uint8_t)0,(uint8_t)3*4,rgbCode);
}