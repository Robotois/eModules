# LCD Module

This module allows the Raspberry PI to display messages in a LCD display. The [LCD display](https://www.adafruit.com/products/181) we use is very popular in electronic projects and we can show messages in a 16x2 characters format.

The design of this module can be resumed in the following features:

* We use the IC [MCP23008](http://www.microchip.com/wwwproducts/en/MCP23008) as interface with the LCD display.
 * We use the MCP23008 because it is a 8-bit digital Input/Output (IO) expander and it uses the I2C port.
 * This means that from the Raspberry PI we will have extra 8 IO that will be managed using the I2C port. By using this device we are reducing the digital IOs we use from the Raspberry PI, and therefore we use them for other applications.
 * We configured the MCP23008 to communicate to the [HD44780U](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf) (LCD driver) using a 4-bit interface.
* There is a trimpot to manually adjust the brightness of the LCD.
* We configured the MCP23008 such that we can connect to the Shield up to 4 LCD modules, this can be done using jumpers and by this way we change the MCP23008 I2C address.
