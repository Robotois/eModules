/*
 * File:   ADS1015.h
 * Author: yova
 *
 * Created on 19 de mayo de 2016, 08:29 PM
 */

#ifndef ADS1015_H
#define	ADS1015_H

#include <stdint.h>

#define ADS1015_DEFAULT_ADDRESS 0x48 // Conversion Register

#define ADS1015_CONV_REG 0x00 // Conversion Register
#define ADS1015_CONFIG_REG 0x01 // Configuration Register

#define ADS1015_SENSOR1 0x04 //- Sensor 1 address
#define ADS1015_SENSOR2 0x05 //- Sensor 2 address
#define ADS1015_SENSOR3 0x06 //- Sensor 3 address
#define ADS1015_SENSOR4 0x07 //- Sensor 4 address

#define ADS1015_512_GAIN 0x04 //- 0.512v gain
#define ADS1015_1024_GAIN 0x03 //- 1.024v gain
#define ADS1015_2048_GAIN 0x02 //- 2.048v gain
#define ADS1015_4096_GAIN 0x01 //- 4.096v gain
#define ADS1015_6144_GAIN 0x00 //- 6.144v gain

#define ADS1015_128SPS 0x00 //- Data Rate: 128 Samples Per Second
#define ADS1015_250SPS 0x01 //- Data Rate: 250 Samples Per Second
#define ADS1015_490SPS 0x02 //- Data Rate: 490 Samples Per Second
#define ADS1015_920SPS 0x03 //- Data Rate: 920 Samples Per Second
#define ADS1015_1600SPS 0x04 //- Data Rate: 1600 Samples Per Second

class ADS1015 {
public:
    ADS1015(uint8_t _addr = 0x00);
    ADS1015(const ADS1015& orig);
    virtual ~ADS1015();

    void selectInput(uint8_t _inputAdd,uint8_t _gain);
    // - We may need a function to set the Sample Rate
    float readInput();
    int16_t readRawInput();
    int16_t fullRangeMeas(uint16_t reading);

    void selectModule();
private:
    uint8_t addr; // - Direccion por default
    uint8_t inputAdd,inputGain;
    float resolution;

    char rBuf[10],wBuf[10];

    void bcm_init();
    void bcm_end();
};

#endif	/* ADS1015_H */
