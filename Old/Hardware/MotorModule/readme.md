# Motor Module

The motor module is powered by the MCU [ATMEGA328](http://www.atmel.com/devices/atmega328.aspx), as you can see this is the same MCU used in the Arduino [UNO](https://www.arduino.cc/en/Main/ArduinoBoardUno). The firmware of this MCU was coded to control two motors using PWM signals. Until the last version of this module, the firmware for the ATMEGA328 is coded in C language (AVR).

This module has the following features:

* An open firmware for the ATMEGA328, this means that you can modify the code or even use Arduino sketches. The module has an SPI interface for programming the MCU.

* This module is ready for controlling motors without feedback, this means that we can control the direction of rotation, and control the speed by PWM signals.

* Also, the motor module has the necessary components to implement speed and direction control using quadrature encoder sensors. The quadrature sensors provide a reliable feedback for controlling the speed of the motor and therefore we can control the speed of the wheels of a robot.

* There are two lines of the RJ25 connector that provide the voltage for the motors, the advantage of this configuration is that we will have a better current flow trough the cables. The voltage to power up the motors is taken directly from the batteries. The typical voltages of a LiPo battery are: 7.4V for a two cell in series (2S) configuration and 11.1V for 3 cells in series (3S).

* The driver for the motors consists of the IC [TB6612FNG](https://www.sparkfun.com/products/9457), this IC was chosen because it is basically a Mosfet H-bridge and it is efficient enough for small robot applications.
