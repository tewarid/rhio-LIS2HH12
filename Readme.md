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
* Operating Modes: A set of functions to configure generic options of the sensor like frequency, bandwidth, low pass filter, software reset, debug, axis, etc.
* Reading Acceleration 

## Main functions

* begin()
* setFrequency(ODR)
* setAxis(ZYX)
* setFS(FS)
* getAccel(&x, &y, &z)

On the "set" functions you need to pass a table's decimal number to set the parameters.

## License

This library was developed by rhomb.io and has a GNU/GPL v3 license. For more information, check the License file.
