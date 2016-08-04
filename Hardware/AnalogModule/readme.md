# Analog Module

This module allows the Raspberry PI to read analog signals, it is specially designed for reading signals coming from analog sensors, such as Light sensor and Temperature just to mention a few ones.

The analog module consists of the IC [ADS1015](http://www.ti.com/product/ADS1015) as you can see in the [schematics](AnalogModule-0.2.pdf). The analog module communicates to the Raspberry PI using the I2C port and we didn't use any digital Input/Output. With this module we can read up to 4 sensors or analog inputs, and the maximum input value for the analog signals is 5V.

The ADS1015 has an input (A0) designed for configuring the I2C address, in our schematics by default this input is set to LOW (0 logic value), but using a jumper this input can be set to HIGH, which is very useful when we want to connect two modules and therefore we would be able to read up to 8 sensors.
