# Shield Module
This folder contains the [Eagle](https://cadsoft.io/) files for the Shield Module. It is provided a pdf file of the [schematics](Shield-0.6.pdf), that way it is easier to get an idea of what it contains.

The design of the Shield can be resumed in the following features:

* A reverse polarity protection circuit. The name of this circuit is very intuitive, it protects the Shield and the whole system (Raspberry PI and modules) from negative voltage. This problem happens if we connect the batteries the wrong way.  There is actually a lot of information about this circuit, I would recommend this [video](https://www.youtube.com/watch?v=IrB-FPcv1Dc).

* The load switch, which allows us to manually turn on and off the voltage from the batteries.
Since the Raspberry PI automatically starts when the power supply is active, we want to control when to turn it on, and also we want to disconnect the power supply from the PI (and the whole system) when we are done with our projects. With this load switch we can cut-off the power supply without having to disconnect the battery at all.

* A Buck converter, this is a DC-DC converter, which steps down the voltage from the batteries, since the voltage allowed is in the range of 6V to 12V. The configuration for this converter is a switching regulator, and it will provide the 5V voltage required for the Raspberry PI and the modules.

* Level shifters for I2C communication, these modules protects the I2C port of the PI from an incoming signal greater than 3.3V. We use this shifters because some of the modules we designed operates at 5V.

* In general all the modules connects to the Shield using a RJ25 connector, which consists of 6 lines, two for power supply, two for I2C communication (SDA and SCL) and two digital inputs/outputs. These connectors are generic, which means that we can connect any module to any connector.

* The RJ25 connectors for Motors/Servos modules are different because we use two lines to power the motors/servos. The power supply for the motors/servos is taken directly from the batteries (except for the basic servo module, it takes the power supply from the 5V of the Shield).
