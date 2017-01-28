/* 
 * File:   MCP23008.h
 * Author: yova
 *
 * Created on 27 de mayo de 2016, 07:57 PM
 */

#ifndef MCP23008_H
#define	MCP23008_H

#define MCP23008_ADDRESS 0x20 // - Default Address
#define MCP23008_INPUT 0x01
#define MCP23008_OUTPUT 0x00
#define MCP23008_HIGH 0x01
#define MCP23008_LOW 0x00
#define MCP23008_PULL_UP_EN 0x01
#define MCP23008_PULL_UP_DIS 0x00

#define MCP23008_IODIR 0x00 //- IO Direction reg
#define MCP23008_IPOL 0x01 // - Input Polarity reg
#define MCP23008_GPINTEN 0x02 // - Interrupt On Change Control reg
#define MCP23008_DEFVAL 0x03 // - Default Compare register for Interrupt On Change
#define MCP23008_INTCON 0x04 // - Interrupt Control reg
#define MCP23008_IOCON 0x05 // - Configuration register
#define MCP23008_GPPU 0x06 // - Pull-Up Resistor Configuration register
#define MCP23008_INTF 0x07 // - Interrupt Flag register
#define MCP23008_INTCAP 0x08 // - Interrupt Capture Register
#define MCP23008_GPIO 0x09 // - Port Register
#define MCP23008_OLAT 0x0A // - Output Latch register


class MCP23008 {
public:
    MCP23008(uint8_t _addr = 0x00);
    MCP23008(const MCP23008& orig);
    virtual ~MCP23008();
    
    void setDir(uint8_t *pin_array,uint8_t dir,uint8_t pin_count);
    void setDir(uint8_t _pin,uint8_t dir);
    void setPullUp(uint8_t *pin_array,uint8_t dir,uint8_t pin_count);
    
    uint8_t readGPIO();
    void writeGPIO(uint8_t gpio);
    void writeMultiGPIO(uint8_t* pin_array, uint8_t *pin_data, uint8_t pin_count);
    void writeMultiGPIO(uint8_t* pin_array, uint8_t pin_data, uint8_t pin_count);
    void digitalWrite(uint8_t pin, uint8_t val);
    uint8_t digitalRead(uint8_t pin);
    
    void release();
private:
    uint8_t slave_addr;
    char rBuf[10],wBuf[10];
    
    void selectModule();
    
    void bcm_init();
    void bcm_end();

};

#endif	/* MCP23008_H */

