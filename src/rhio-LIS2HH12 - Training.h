/**
 * Rhomb.io LIS2HH12 library
 *
 * @author Jose Francisco Martí Martín
 * @version Example
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <Arduino.h>
#include <Wire.h>

#ifndef LIS2HH12_h
#define LIS2HH12_h

/*************************** REGISTER MAP ***************************/
#define LIS2HH12_CTRL1 0x20    // Control Register (R/W)
#define LIS2HH12_CTRL4 0x23    // Control Register (R/W)
#define LIS2HH12_CTRL5 0x24    // Control Register (R/W)
#define LIS2HH12_OUT_X_L 0x28  // X-Axis_Low BYTE (R)
#define LIS2HH12_OUT_X_H 0x29  // X-Axis_High BYTE (R)
#define LIS2HH12_OUT_Y_L 0x2A  // Y-Axis_Low BYTE (R)
#define LIS2HH12_OUT_Y_H 0x2B  // Y-Axis_High BYTE (R)
#define LIS2HH12_OUT_Z_L 0x2C  // Z-Axis_Low BYTE (R)
#define LIS2HH12_OUT_Z_H 0x2D  // Z-Axis_High BYTE (R)

class LIS2HH12 {
 public:
  /***************************************************************************
   *                          Constructor
   **************************************************************************/

  LIS2HH12();
  uint8_t I2CAddress;

  /***************************************************************************
   *                          Initialization
   **************************************************************************/

  /**
   * @fn void begin();
   *  @brief Set the basics to run the sensor.
   *  I2C default communication.
   */
  void begin();

  /***************************************************************************
   *                          Basic function
   **************************************************************************/

  /**
   * @fn void setBasicConfig()
   *  @brief Set the basics to run the sensor.
   */
  void setBasicConfig();

  /***************************************************************************
   *                          Operating Modes
   **************************************************************************/

  /**
   * @fn void setFrequency(uint8_t ODR);
   *  @brief Set the sample measure frequency.
   *  There is a decimation filter cutoff frequency that depends on ODR.
   *  @param ODR decimal value to set the frequency.
   *  --------------------------------------------------------------------------
   *  Frequency |   ODR   |  BW=400 Hz  |  BW=200 Hz  |  BW=100 Hz  |  BW=50 Hz
   * ---------------------------------------------------------------------------
   *                      |                   Discarded samples
   * ---------------------------------------------------------------------------
   *   800 Hz   |   96    |      1      |      4      |      7      |     14
   *   400 Hz   |   80    |      1      |      1      |      4      |     7
   *   200 Hz   |   64    |      1      |      1      |      1      |     4
   *   100 Hz   |   48    |      1      |      1      |      1      |     1
   *   50  Hz   |   32    |      1      |      -      |      -      |     -
   *   10  Hz   |   16    |      1      |      -      |      -      |     -
   * Power Down |    0    |             |             |             |
   */
  void setFrequency(uint8_t ODR);

  /**
   * @fn void setAxis(uint8_t ZYX);
   *  @brief Set which axis is being read.
   *  @param ZYX decimal value to set the axis.
   * -----------------------
   *    Axis  |   ZYX
   * ----------------------
   *    ZYX   |    7
   *    ZY    |    6
   *    ZX    |    5
   *    Z     |    4
   *    YX    |    3
   *    Y     |    2
   *    X     |    1
   *   None   |    0
   */
  void setAxis(uint8_t ZYX);

  /**
   * @fn void setFS(uint8_t FS);
   *  @brief Set the accelerometer full scale.
   *  @param FS decimal value to set the full scale.
   * ----------------------------------
   *   +/- g  |   Sensitivity  |  FS
   * ---------------------------------
   *     2    |      0.061     |  0
   *     4    |      0.122     |  32
   *     8    |      0.244     |  48
   */
  void setFS(uint8_t FS);

  /**
   * @fn void setSoftReset();
   *  @brief Give the posibility to do a reset.
   */
  void setSoftReset();

  /***************************************************************************
   *                   Reading Accerlation Data Modes
   **************************************************************************/

  /**
   * @fn char getAccel(float* x, float* y, float* z);
   *  @brief Get the data accel in g.
   *  It's the same mode as getAccelmG(float* x, float* y, float* z) but
   *  when it is measured in g. All parameters are pointers.
   *  @param x
   *  @param y
   *  @param z
   */
  void getAccel(float* x, float* y, float* z);

  /***************************************************************************
   *                   Private functions
   **************************************************************************/
 private:
  uint8_t readRegister(uint8_t regis);
  void readAccel(float* x0, float* y0, float* z0);
  void writeRegister(uint8_t val, uint8_t regis, uint8_t bt);
  char readbit(uint8_t regis, int loc);
  float convert(int g, int axis);
};

#endif