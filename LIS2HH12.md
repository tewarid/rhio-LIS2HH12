# LIS2HH12  

LIS2HH12 is ultra-low-power high-performance three-axis linear accelerometer sensor integrated on the Halley motherboard. It can measure acceleration and also temperature, due to the embedded temperature sensor.  

The sensor has two communication interfaces, SPI and I2C. The Halley has available I2C interface. It's able to measure accelerations with output data rates from 10 Hz to 800 Hz.

## Features  
  
There are three full-scale options +/- (2 g, 4 g, 8 g).  The LIS2HH12 has an integrated fist-in, first-out (FIFO) buffer allowing to the user store data and save power consumption.  
The developer has the posibility to configure measure frequency, filters, operating modes, interruptions and FIFO.

LIS2HH12 has two independent programmable interrupt generator. It allows to set wake-up, free-fall or 6D and 4D orientation detection.  

### Interruptions connections to Halley  
  
LIS2HH12 INT1 is connected to IO Expander's GPIO0 and INT2 is connected to INT3(J204 S200 socket). 

## Applications  

This sensor has so different applications like motion-controlled user interface, gaming and virtual reality, podometer, display orientation, click/double click recognition, impact recognition and logging or vibration monitoring and compensation.  
  
## Using the Halley's accelerometer LIS2HH12
