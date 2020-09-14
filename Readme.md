# rhio-LIS2HH12

This is a portable library based on Arduino to work with the LIS2H12 accelerometer. It was developed by rhomb.io and it is open source. The LIS2HH12 accelerometer has 3-axis, a temperature sensor and other advanced features.

## Features

* Read by I2C
* Read single or all axis
* Configure two interruption generators and interruption pins
* Read acceleration in g or mg
* Read temperature in ºC
* Configure all sensor options

## Library structure

This library was designed to be easy to read with the following sections on the rhio-LIS2HH12.h and rhio-LIS2HH12.cpp

* Initialization: The functions of this section are used to start the sensor and configure I2C.
* Basic function: Basic configuration of the sensor.
* Application: Two functions to easily run the sensor advanced options.
* Operating Modes: A set of functions to configure generic options of the sensor like frequency, bandwidth, low pass filter, software reset, debug, axis, etc.
* Reading Acceleration Data Modes : You can read the different modes of data.
    * Use without conversion if you want to set the high pass filter.
    * Get data in g or mg units. Each one can be read with three different functions.
* High pass filter (HPF): The function for setting HPF.
* Interruption generation (IG): This section is needed if you want to read the interruption from the pads. With this functions you enable the IG 1 or 2 on the interruption pads that you need.
* Inertial Interrupt: The main function is "setIntMode(IntMode, IG)" because with it you can develop different applications. There are other important ones for enabling the axis interruption. Get this interuptions and set the interruption behavior for minimum duration of the signal to create an interruption, a threshold interruption, etc.
* FIFO: Use if you want to save data. With this you configure the FIFO, enable FIFO, enable deep FIFO and how deep it will be. Set FIFO interruption signals or read signals to know the FIFO status.
* STATUS: "Get" functions to know well the system behavior.
* Temp: It's a function to measure the temperature.

## Main functions

* begin()
* setFrequency(ODR)
* setAxis(ZYX)
* setFS(FS)
* getAccel(&x, &y, &z)

On the "set" functions you need to pass a table's decimal number to set the parameters.

## Interruptions

As stated before, there are two posibilities here:

* The first one, you have two interrupt generators that you configure separately. You can read these interruptions with some get functions.
* The other one, you can select which interrupt generator is enabled in the INT pads. Even though these generators are configured, some of them can only be read on the INT pads.

## License

This library was developed by rhomb.io and has a GNU/GPL v3 license. For more information, check the License file.
