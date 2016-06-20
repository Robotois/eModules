/* 
 * File:   BCMSetup.h
 * Author: yova
 *
 * Created on 7 de junio de 2016, 10:27 PM
 */

#ifndef BCMSETUP_H
#define	BCMSETUP_H

class BCMSetup {
public:
    BCMSetup();
    BCMSetup(const BCMSetup& orig);
    virtual ~BCMSetup();
    
    uint8_t bcm_init();
    void bcm_end();
    
    void set_slave(uint8_t _addr);
    
    uint8_t read_register(char* regAddr, char* buf,uint16_t len);
    uint8_t write(char* buf, uint16_t len);
private:

};

#endif	/* BCMSETUP_H */

