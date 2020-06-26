# rhio-LIS2HH12

This a portable library based on Arduino to work with the LIS2H12 accelerometer. It has been developed by rhomb.io and is open source. LIS2HH12 accelerometer has 3-axis, temperature sensor and other advanced options.

## Features  

+ Read by I2C
+ Read single or all axis  
+ Configure two interruptions generator and interruption pins
+ Read acceleration in g or mg 
+ Read temperature in ºC
+ Configure all sensor option

## Library structure

The library design try to be easy visible with the following sections on the rhio-LIS2HH12.h and rhio-LIS2HH12.cpp.

+ Initialization: The functions of this section are used for begin the sensor and configure I2C.  

+ Basic function: Basic configuration of the sensor.

+ Application: Two function for easy run of the sensor advanced options.

+ Operating Modes: With this functions you configure generic options of the sensor like frequency, bandwidth, low pass filter, software reset, debug, axis, etc. 

+ Reading Acceleration Data Modes : You can read the differents modes of data. 
  * Without convert, this is very helpful if you want to set the high pass filter.  
  *  You can read in g or mg unit. You can read each one with three differents functions.

+ High pass filter (HPF): The function for set HPF.  
  
+ Interruption generation (IG): This section is very important if you want to read the interruption from the pads. With this functions you enable the IG 1 or 2 on the interruptions pads that you need.  

+ Inertial Interrupt: One of the most important functions here is the "setIntMode(IntMode, IG)" because with it you can develop differents applications. There are other importants for enable axis interruption, get this interuptions and set the interruption behavior for minimum duration of the signal to create an interruption, threshold interruption, etc.  
  
+ FIFO: Very usefull if you want to save data. With this you configure the FIFO, enable FIFO, enable deep FIFO and what deep. Set FIFO interruption signals or read signal to know the FIFO status.  
  
+ STATUS: Get functions to know well the system behavior.

+ Temp: It's an only one function to measure the temperature

## Main functions 

+ begin() 
+ setFrequency(ODR)
+ setAxis(ZYX)
+ setFS(FS) 
+ getAccel(&x, &y, &z)

On the set function you need to pass a table's decimal number to set the parameters. 

## Interruptions  

Like we saw before, we have two posibilities here. First, you have two interrupt generator that you configure separate. And you can read this interruptions with some get functions. Also you can select what interrupt generator is enable in the INT pads. Although you have other configure interruption function that only can read by the INT path.

## License  

This library was developed by rhomb.io and has a GNU/GPL v3 license. For more information, check the License file.
