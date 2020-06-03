/**
 * Rhomb.io lis2hh12 library
 *
 * @author Jose Francisco Martí Martín
 * @version 1.0.0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#ifndef LIS2HH12_h
#define LIS2HH12_h

#define LIS2HH12_SPI_CLOCK 10000000  // Max
#define LIS2HH12_SPI_MODE SPI_MODE0

/*************************** REGISTER MAP ***************************/
#define LIS2HH12_RESERVED0 0x00  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED1 0x01  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED2 0x02  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED3 0x03  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED4 0x04  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED5 0x05  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED6 0x06  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED7 0x07  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED8 0x08  // Reserved. Do Not Access.
#define LIS2HH12_RESERVED9 0x09  // Reserved. Do Not Access.
#define LIS2HH12_RESERVEDA 0x0A  // Reserved. Do Not Access.
#define LIS2HH12_TEMP_L 0x0B     // Temperature Low Significant Byte (R)
#define LIS2HH12_TEMP_H 0x0C     // Temperature High Significant Byte (R)
#define LIS2HH12_RESERVEDE 0x0E  // Reserved. Do Not Access.
#define LIS2HH12_WHO_AM_I 0x0F   // Device ID. (R)
#define LIS2HH12_ACT_THS 0x1E    // ? (R/W)
#define LIS2HH12_ACT_DUR 0x1F    // ? (R/W)
#define LIS2HH12_CTRL1 0x20      // Control Register (R/W)
#define LIS2HH12_CTRL2 0x21      // Control Register (R/W)
#define LIS2HH12_CTRL3 0x22      // Control Register (R/W)
#define LIS2HH12_CTRL4 0x23      // Control Register (R/W)
#define LIS2HH12_CTRL5 0x24      // Control Register (R/W)
#define LIS2HH12_CTRL6 0x25      // Control Register (R/W)
#define LIS2HH12_CTRL7 0x26      // Control Register (R/W)
#define LIS2HH12_STATUS 0x27     // Status Data Register (R)
#define LIS2HH12_OUT_X_L 0x28    // X-Axis_Low BYTE (R)
#define LIS2HH12_OUT_X_H 0x29    // X-Axis_High BYTE (R)
#define LIS2HH12_OUT_Y_L 0x2A    // Y-Axis_Low BYTE (R)
#define LIS2HH12_OUT_Y_H 0x2B    // Y-Axis_High BYTE (R)
#define LIS2HH12_OUT_Z_L 0x2C    // Z-Axis_Low BYTE (R)
#define LIS2HH12_OUT_Z_H 0x2D    // Z-Axis_High BYTE (R)
#define LIS2HH12_FIFO_CTRL 0x2E  // FIFO Control (R/W)
#define LIS2HH12_FIFO_SRC 0x2F   // FIFO ? (R)
#define LIS2HH12_IG_CFG1 0x30    // Interrupt Generator 1 configuration (R/W)
#define LIS2HH12_IG_SRC1 0x31    // Interrupt Generator 1 status Register (R)
#define LIS2HH12_IG_THS_X1 0x32  // Interrupt generator 1 X Threshold (R/W)
#define LIS2HH12_IG_THS_Y1 0x33  // Interrupt Generator 1 Y Threshold (R/W)
#define LIS2HH12_IG_THS_Z1 0x34  // Interrupt Generator 1 Z Threshold (R/W)
#define LIS2HH12_IG_DUR1 0x35    // Interrupt Generator 1 Duration (R/W)
#define LIS2HH12_IG_CFG2 0x36    // Interrupt Generator 2 configuration (R/W)
#define LIS2HH12_IG_SRC2 0x37    // Interrupt Generator 2 status Register (R)
#define LIS2HH12_IG_THS2 0x38    // Interrupt generator 2 Threshold (R/W)
#define LIS2HH12_IG_DUR2 0x39    // Interrupt Generator 2 Duration (R/W)

#define LIS2HH12_XL_REFERENCE 0x3A  // Reference X Low (R/W)
#define LIS2HH12_XH_REFERENCE 0x3B  // Reference X High (R/W)
#define LIS2HH12_YL_REFERENCE 0x3C  // Reference Y Low (R/W)
#define LIS2HH12_YH_REFERENCE 0x3D  // Reference Y High (R/W)
#define LIS2HH12_ZL_REFERENCE 0x3E  // Reference Z Low (R/W)
#define LIS2HH12_ZH_REFERENCE 0x3F  // Reference Z High (R/W)

/*********************SET MACROS*********************/

#define LIS_ENABLE 0
#define LIS_DISABLED 1
#define IG1 2
#define IG2 3
#define INT1 4
#define INT2 5
#define PP 6
#define OD 7
#define HINT 8
#define LINT 9
#define ENABLE_INT1 10
#define ENABLE_INT2 11
#define DISABLED_INT1 12
#define DISABLED_INT2 13
#define CHANGEALPF 14
#define NOCHANGEALPF 15
#define OFFDLPF 16
#define ONDLPF 17
#define ONDHPF 18

class LIS2HH12 {
 public:
  //*******Constructor*******

  LIS2HH12();
  uint8_t I2CAddress;
  float zerox, zeroy, zeroz;

  /***************************************************************************
   *                          Initialization
   **************************************************************************/

  /**
   * @fn void begin();
   *  @brief Set the basic to run the sensor
   *  I2C default communication
   */
  void begin();

  /**
   * @fn void setI2C(uint8_t Address);
   *  @brief Change I2C address
   *  @param Address
   */
  void setI2C(uint8_t Address);

  /***************************************************************************
   *                          Basic function
   **************************************************************************/

  /**
   * @fn void setBasicConfig()
   *  @brief Set the basic to run the sensor
   */
  void setBasicConfig();

  /***************************************************************************
   *                          Apliccation
   **************************************************************************/

  /**
   * @fn char getIsMoving();
   *  @brief return true if the sensor is moving
   *  All getActiveTime depend of this function.
   */
  uint8_t getIsMoving();

  /**
   * @fn float getActiveTime();
   *  @brief return a time moving value
   */
  float getActiveTime();

  /**
   * @fn float getActiveTime2();
   *  @brief return a time moving value including a 10 min maximum waiting
   */
  float getActiveTime2();

  /***************************************************************************
   *                          Operating Modes
   **************************************************************************/

  /**
   * @fn void setFrequency(uint8_t ODR);
   *  @brief set the sample measure frequency
   *  There are a decimation filter cutoff frequency that depend of ODR
   *  @param ODR decimal value to set the frequency
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
   *  @brief set the measure axis
   *  @param ZYX decimal value to set the axis
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
   * @fn setDLPF(char DLPF);
   *  @brief set digital low pass filter
   *  Default mode is OFFDLPF. if you use ONDLPF, you can't use decimator
   *  @param DLPF switch binary value
   *  There are two specific macros: ONDLPF and OFFDLPF
   */
  void setDLPF(char DLPF);

  /**
   * @fn void setALPF(char ALPF);
   *  @brief set the analog low pass filter
   *  The analog ALPF have a default condition bandwidth of ODR/2 if you
   *  don't set the ALPF variable.
   *  @param ALPF switch binary value
   * There are two specific macros: NOCHANGEALPF and CHANGEALPF
   */
  void setALPF(char ALPF);

  /**
   * @fn setanalogBandwidth(uint8_t BW);
   *  @brief set the analog filer bandwitch
   *  @param BW decimal value to set the bandwitch
   * -----------------------
   *   (BW)Hz |    BW
   * ----------------------
   *    400   |    0
   *    200   |    64
   *    100   |    128
   *    50    |    192
   */
  void setanalogBandwidth(uint8_t BW);

  /**
   * @fn setdigitalLPF(uint8_t LPFcutOff);
   *  @brief set the low pass filter cutoff
   *  @param LPFcutoff decimal value to set the cutoff frequency
   * -----------------------
   * (Cut off)Hz | LPFcutOff
   * ----------------------
   *    ODR/50   |    0
   *    ODR/100  |    32
   *    ODR/9    |    64
   *    ODR/200  |    96
   */
  void setdigitalLPF(uint8_t LPFcutOff);

  /**
   * @fn setActiveInactive(uint8_t threshold, uint8_t duration);
   *  @brief set the active/inactive function
   *  You active this option when pass a threshold parameter
   *  @param threshold decimal value that depend of the LSB value
   *  @param duration decimal value that depend of the LSB value
   *  The threshold is represented by 7 bits bit [6:0], bit7 must be set to 0
   *  The duration is represented by 8 bits
   * ---------------------------------------
   *  Full scale | Threshold LSB value (mg)
   * --------------------------------------
   *      2      |       0.015625
   *      4      |       0.03125
   *      8      |       0.0625
   *---------------------------------------
   *      ODR    | Duration LSB value (s)
   * --------------------------------------
   *      800    |        0.01
   *      400    |        0.02
   *      200    |        0.04
   *      100    |        0.08
   *      50     |        0.16
   *      10     |        0.8
   */
  void setActiveInactive(uint8_t threshold, uint8_t duration);

  /** setIntDataready(char Status, char INT);
   *  @brief set the active/inactive function on a INT pad
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   *  @param INT switch binary value
   *  There are two specific macros for INT: INT1 and INT2
   */
  void setIntDataready(char Status, char INT);

  /**
   * @fn setPolarityINT(char H_Lint);
   *  @brief set the INT polarity
   *  The default polarity is HIGH
   *  @param H_Lint switch binary value
   *  There are two specifics macros for H_LINT: HINT and LINT
   */
  void setPolarityINT(char H_Lint);

  /**
   * @fn void setFS(uint8_t FS);
   *  @brief set the accelerometer full scale
   *  @param FS decimal value to set the full scale
   * ----------------------------------
   *   +/- g  |   Sensitivity  |  FS
   * ---------------------------------
   *     2    |      0.061     |  0
   *     4    |      0.122     |  32
   *     8    |      0.244     |  48
   */
  void setFS(uint8_t FS);

  /**
   * @fn setSelfTest(uint8_t mode);
   *  @brief set selt test
   *  @param mode decimal value to set the test
   * ----------------------------------------
   *        Action            |   mode
   * ---------------------------------------
   *      Normal mode         |    0
   *  Positive sign self-test |    4
   *  Negative sign self-test |    8
   */
  void setSelfTest(uint8_t mode);

  /**
   * @fn setZeroLevel(float zx, float zy, float zz);
   *  @brief Function to set visually the zero level
   *  This function doesn't change nothing in the measure, it's only visual
   *  @param zx
   *  @param zy
   *  @param zz
   *  You choose the exact value for each axis
   */
  void setZeroLevel(float zx, float zy, float zz);

  /**
   * @fn setInt2Boot(char Status);
   *  @brief set boot on the INT2 pad
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setInt2Boot(char Status);

  /**
   * @fn setReboot();
   *  @brief Give the posible to reboot the code
   */
  void setReboot();

  /**
   * @fn setDecimation(uint8_t Dec);
   *  @brief set the samples update
   *  @param Dec decimal value
   * ----------------------------------------
   *       Update accel       |   Dec
   * ---------------------------------------
   *      No decimation       |    0
   *     Every 2 samples      |    16
   *     Every 4 samples      |    32
   *     Every 8 samples      |    48
   */
  void setDecimation(uint8_t Dec);

  /**
   * @fn void setDebug(char Status);
   *  @brief set the debug mode
   *  You need to disabled the digital low pass filter (default mode)
   *  to use decimator
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setDebug(char Status);

  /**
   * @fn void setSoftReset();
   *  @brief Give the posibility to do a reset
   */
  void setSoftReset();

  /**
   * @fn setFDS(char OutData);
   *  @brief set the high pass filter(HPF) or the low pass filter (DLPF)
   *  You need to know that for use DLPF you have to select ONDLP in the
   * function setDLPF(char DLPF); Default value is decimator or DLPF
   *  @param OutData switch binary value
   *  There are two specific macros: ONDHPF and ONDLPF
   *  The accelerometer can't have DLPF and DHPF at the same time.
   */
  void setFDS(char OutData);

  /**
   * @fn setBDU(char Status);
   *  @brief Block data update
   *  If the reading of the acceleration data is particularly slow and can't be
   *  synchronized with either the XYZDA bit or with DRDY signal, it's strongly
   *  recommended to set BDU
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setBDU(char Status);

  /***************************************************************************
   *                   Reading Accerlation Data Modes
   **************************************************************************/

  /**
   * @fn char getAccelmG(float* x, float* y, float* z);
   *  @brief Get the data accel in mg
   *  @return XYZ overwritting the previous data (1)
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   */
  uint8_t getAccelmG(float* x, float* y, float* z);

  /**
   * @fn void getAccelDataReadymG(float* x, float* y, float* z);
   *  @brief Get the data accel in mg when the device is active
   *  If the device is flat, there aren't measure
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   */
  void getAccelDataReadymG(float* x, float* y, float* z);

  /**
   * @fn void getAccelBDUmG(float* x, float* y, float* z);
   *  @brief Get the data accel in mg when the BDU is active
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   *  @see void setBDU(char Status);
   */
  void getAccelBDUmG(float* x, float* y, float* z);

  /**
   * @fn char getAccel(float* x, float* y, float* z);
   *  @brief Get the data accel in g
   *  It's the same mode that getAccelmG(float* x, float* y, float* z) but
   *  with the measure in g
   *  @return XYZ overwritting the previous data (1)
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   */
  uint8_t getAccel(float* x, float* y, float* z);

  /**
   * @fn void getAccelDataReady(float* x, float* y, float* z);
   *  @brief Get the data accel in g when the device is active
   *  It's the same mode that getAccelDataReadymG(float* x, float* y,
   *  float* z) but with the measure in g
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   */
  void getAccelDataReady(float* x, float* y, float* z);

  /**
   * @fn void getAccelBDUmG(float* x, float* y, float* z);
   *  @brief Get the data accel in g with the BDU is active
   *  It's the same model that getAccelBDUmG(float* x, float* y, float* z); but
   *  with the measure in g
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   */
  void getAccelBDU(float* x, float* y, float* z);

  /**
   * @fn void getAccelRAW(int* x, int* y, int* z);
   *  @brief Get the data accel in LSB value
   *  It's a important function when you use the high pass filter. You set
   *  with this value the reference register.
   *  It's important to know how function the accelerometer measure.
   *  @param x
   *  @param y
   *  @param z
   *  All parameters are pointers
   *  @see convert(int g, int axis);
   *  You can see the explication in this private function
   */
  void getAccelRAW(int* x, int* y, int* z);

  /***************************************************************************
   *                          High Pass Filter
   **************************************************************************/

  /**
   * @fn void setIntHPFData(uint8_t IntHPF);
   *  @brief Set the reference value to generate a interruption
   *  You can select that the interrupt generator use the high pass filter
   *  data or the normal data
   *  @param IntHPF
   * -------------------------------
   *   INT1   |   INT2   |  IntHPF
   * ------------------------------
   *   data   |   data   |    0
   *   data   |  dataHPF |    1
   *  dataHPF |   data   |    2
   *  dataHPF |  dataHPF |    3
   */
  void setIntHPFData(uint8_t IntHPF);

  /**
   * @fn void setHPF(uint8_t HPF);
   *  @brief Select the high pass filter mode
   *  @param HPF
   *-------------------------------
   *        Mode        |   HPF
   * ------------------------------
   *       Normal       |   0
   *   Reference signal |   8
   */
  void setHPF(uint8_t HPF);

  /**
   * @fn setCutOffHPF(uint8_t HPFcutOff);
   *  @brief Select the high pass filter cut off
   *  @param HPFcutOff
   *-----------------------
   * (Cut off)Hz | HPFcutOff
   * ----------------------
   *    ODR/50   |    0
   *    ODR/100  |    32
   *    ODR/9    |    64
   *    ODR/200  |    96
   */
  void setCutOffHPF(uint8_t HPFcutOff);

  /**
   * @fn setReference(uint16_t x, uint16_t y, uint16_t z);
   * @brief Set reference high pass filter LSB value
   * @param x
   * @param y
   * @param z
   */
  void setReference(uint16_t x, uint16_t y, uint16_t z);

  /**
   * @fn sertReferencemG(float x, float y, float z);
   *  @brief Set reference high pass filter mg value
   *  There aren't a set reference in g because it's important to a have a high
   *  resolution in the filter.
   *  @param x
   *  @param y
   *  @param z
   */
  void setReferencemG(float x, float y, float z);

  /***************************************************************************
   *                          Interrupt Generation
   **************************************************************************/

  /**
   * @fn void setIntGenerator1(char INT_1, char INT_2);
   *  @brief Selects where go the interrupt generator 1 (IG1)
   *  You can select if the IG1 go to INT1 pad or/and INT2 pad
   *  @param INT_1
   *  @param INT_2
   *  There are four specific macros (DISABLED_INT1, DISABLED_INT2, ENABLE_INT1
   *  and ENABLE_INT2)
   */
  void setIntGenerator1(char INT_1, char INT_2);

  /**
   * @fn void setIntGenerator2(char INT_1, char INT_2);
   *  @brief Selects where go the interrupt generator 2 (IG2)
   *  You can select if the IG2 go to INT1 pad or/and INT2 pad
   *  @param INT_1
   *  @param INT_2
   *  There are four specific macros (DISABLED_INT1, DISABLED_INT2, ENABLE_INT1
   *  and ENABLE_INT2)
   */
  void setIntGenerator2(char INT_1, char INT_2);

  /***************************************************************************
   *                          Inertial Interrupt
   **************************************************************************/

  /**
   * @fn void setIntMode(uint8_t IntMode, char IG);
   *  @brief Sets interrupt generator (IG) mode
   *  You select the IG's mode
   *  @param IntMode
   *  @param IG
   * -------------------------------------------------
   *             IntMode                |  IntMode
   * ------------------------------------------------
   *   OR combination of axis requests  |    0
   *   6-direction movement recognition |    64
   *   AND combination of axis requests |    128
   *   6-direction position recognition |    192
   *
   *  There are two specific macros to IG (IG1 and IG2)
   */
  void setIntMode(uint8_t IntMode, char IG);

  /**
   * @fn void setXYZIE(char Status, char IG);
   *  @brief Enable or disabled all interrupt request
   *  You need to select on what interrupt generator want to enable or disabled
   *  interrupt request
   *  @param Status
   *  @param IG
   *  There are two specific macros to IG (IG1 and IG2) and two generic to
   *  Status (LIS_DISABLED and LIS_ENABLE)
   */
  void setXYZIE(char Status, char IG);

  /**
   * @fn void setXIE(uint8_t XIE, char IG);
   *  @brief Enable or disabled X axis interrupt request
   *  You need to select on what interrupt generator want to enable or disabled
   *  X axis interrupt request
   *  @param XIE
   *  @param IG
   *  -------------------
   *  XHIE | XLIE | XIE
   *  --------------------
   *   0   |  0   |  0
   *   0   |  1   |  1
   *   1   |  0   |  2
   *   1   |  1   |  3
   *  There are two specific macros to IG (IG1 and IG2)
   */
  void setXIE(uint8_t XIE, char IG);

  /**
   * @fn void setYIE(uint8_t YIE, char IG);
   *  @brief Enable or disabled Y axis interrupt request
   *  You need to select on what interrupt generator want to enable or disabled
   *  Y axis interrupt request
   *  @param YIE
   *  @param IG
   *  -------------------
   *  YHIE | YLIE | YIE
   *  --------------------
   *   0   |  0   |  0
   *   0   |  1   |  4
   *   1   |  0   |  8
   *   1   |  1   |  12
   *  There are two specific macros to IG (IG1 and IG2)
   */
  void setYIE(uint8_t YIE, char IG);

  /**
   * @fn void setZIE(uint8_t ZIE, char IG);
   *  @brief Enable or disabled Z axis interrupt request
   *  You need to select on what interrupt generator want to enable or disabled
   *  Z axis interrupt request
   *  @param ZIE
   *  @param IG
   *  -------------------
   *   ZHIE | ZLIE | ZIE
   *  --------------------
   *    0   |  0   |  0
   *    0   |  1   |  16
   *    1   |  0   |  32
   *    1   |  1   |  48
   *  There are two specific macros to IG (IG1 and IG2)
   */
  void setZIE(uint8_t ZIE, char IG);

  /**
   * @fn uint8_t getINT(char IG);
   *  @brief Gets the interrupt data of or/and axis
   *  You need to select on what interrupt generator want to get data
   *  @param IG
   *  @return The interrupt generator value
   *  The return depend of the interrupt mode
   *  There are two specific macros to IG (IG1 and IG2)
   */
  uint8_t getINT(char IG);

  /**
   * @fn void getAxisHInt(char* xh, char* yh, char* zh, char IG);
   *  @brief Gets interrupt data
   *  xh, yh, and zh are active when the the interrupt contition is verified
   *  The axis are active when the data exceed the threshold and the the
   *  duration is longer than the minimum duration set.
   *  You need to select on what interrupt generator want to get data.
   *  @param IG
   *  @param xh
   *  @param yh
   *  @param zh
   *  There are two specific macros to IG (IG1 and IG2)
   *  @see setMinDurationIG(uint8_t Duration, char IG);
   *  @see setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z);
   *  @see setThresholdIG2(uint8_t Threshold);
   */
  void getAxisHInt(uint8_t* xh, uint8_t* yh, uint8_t* zh, char IG);

  /**
   * @fn void getAxisLInt(char* xl, char* yl, char* zl, char IG);
   *  @brief Gets interrupt data
   *  xl, yl, and zl are active when the the interrupt contition isn't verified
   *  The axis are active when the data doesn't exceed the threshold.
   *  You need to select on what interrupt generator want to get data.
   *  @param IG
   *  @param xl
   *  @param yl
   *  @param zl
   *  There are two specific macros to IG (IG1 and IG2)
   *  @see setMinDurationIG(uint8_t Duration, char IG);
   *  @see setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z);
   *  @see setThresholdIG2(uint8_t Threshold);
   */
  void getAxisLInt(uint8_t* xl, uint8_t* yl, uint8_t* zl, char IG);

  /**
   * @fn void setMinDurationIG(uint8_t Duration, char IG);
   *  @brief Sets time
   *  Selects the minium time that data need to be higher than threshold to
   *  generat an interruption,
   *  You need to select on what interrupt generator want to set the duration.
   *  @param IG
   *  @param Duration
   *  There are two specific macros to IG (IG1 and IG2)
   *  ---------------------------------------
   *      ODR    | Duration LSB value (ms)
   *    --------------------------------------
   *      800    |        1.25
   *      400    |        2.5
   *      200    |        5
   *      100    |        10
   *      50     |        20
   *      10     |        100
   *  The duration is represented by 7 bits DUR[6:0]
   *  Duration time is measured in N/ODR, where N is the duration
   *  register content
   *  Example: ODR = 10 Hz -> Duration LSB value is 100 ms
   *  If I select 100 like Duration, the real duration is 100 * 100 = 10000 ms
   */
  void setMinDurationIG(uint8_t Duration, char IG);

  /**
   * @fn void setDecrementIG(char Status, char IG);
   *  @brief Sets the interrupt genearator performance
   *  The generator disable immeadiatly the interruption when the condition
   *  doesn't verified. It's important to see the datasheet section to
   *  undertand how it function.You need to select on what interrupt generator
   *  want to set the decrement function.
   *  @param IG
   *  @param Status
   *  There are two specific macros to IG (IG1 and IG2) two generic to
   *  Status (LIS_DISABLED and LIS_ENABLE)
   */
  void setDecrementIG(char Status, char IG);

  /**
   * @fn void setWaitIG(char Status, char IG);
   *  @brief Sets the interrupt genearator performance
   *  The generator wait when the interrupt contition is verified and the same
   *  when leave to be verified. It's important to see the datasheet section to
   *  undertand how it function.
   *  You need to select on what interrupt generator want to set the wait
   *  function.
   *  @param IG
   *  @param Status
   *  There are two specific macros to IG (IG1 and IG2) two generic to
   *  Status (LIS_DISABLED and LIS_ENABLE).
   */
  void setWaitIG(char Status, char IG);

  /**
   * @fn void setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z);
   *  @brief Sets the interrupt generator 1 threshold
   *  Interrupt generator 1 allows selecting a different threshold for
   *  each axis
   *  @param X
   *  @param Y
   *  @param Z
   *  ---------------------------------------
   *    Full scale | Threshold LSB value (mg)
   *    --------------------------------------
   *        2      |           8
   *        4      |           16
   *        8      |           31
   *    ---------------------------------------
   *  The threshold is represented by 8 bits
   *  Example: Full scale = 2 -> Threshold LSB value is 8 mg
   *  If I select 100 like X, the real X threshold is 100 * 8 = 800 mg and the
   *  same for the other axis
   */
  void setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z);

  /**
   * @fn void setThresholdIG2(uint8_t Threshold);
   *  @brief Sets the interrupt generator 2 threshold
   *  Interrupt generator 2 supports the same threshold to all axis
   *  @param Threshold
   *  ---------------------------------------
   *    Full scale | Threshold LSB value (mg)
   *    --------------------------------------
   *        2      |           8
   *        4      |           16
   *        8      |           31
   *    ---------------------------------------
   *  The threshold is represented by 8 bits
   *  Example: Full scale = 4 -> Threshold LSB value is 16 mg
   *  If I select 100 like Threshold, the real threshold is 100 * 16 = 1600 mg
   *  to all axis
   */
  void setThresholdIG2(uint8_t Threshold);

  /**
   * @fn void setLatchedIG(char Status, char IG);
   *  @brief Request must be latched or not
   *  If the latched is enable, whenever an interrupt condition is applied, the
   *  interrupt signal remain high even if the condition returns to a
   *  non-interrupt status until a read of the interruption. You need to select
   *  on what interrupt generator want to set the latched function.
   *  @param Status
   *  @param IG
   *  There are two specific macros to IG (IG1 and IG2) two generic to
   *  Status (LIS_DISABLED and LIS_ENABLE)
   */
  void setLatchedIG(char Status, char IG);

  /**
   * @fn void setPP_OD(char PP_OD);
   *  @brief It allows change the pin behavior from Push-pull to open drain
   *  @param PP_OD
   *  There are two specific macros to PP_OD (PP and OD)
   */
  void setPP_OD(char PP_OD);

  /**
   * @fn void set4Dmode(char Status, char IG);
   *  @brief Set the 4D mode
   *  6D must be configured with setIntMode. If you want to use 4D, you need to
   *  set 6D, also need to set Z axis request to 0. (With the 4D mode you
   *  disabled Z axis)
   *  @param Status
   *  @param IG
   *  There are two specific macros to IG (IG1 and IG2) two generic to
   *  Status (LIS_DISABLED and LIS_ENABLE)
   */
  void set4Dmode(char Status, char IG);

  /***************************************************************************
   *                                  FIFO
   **************************************************************************/

  /**
   * @fn void setEnableFIFO(char Status);
   *  @brief It allows enable the FIFO
   *  @param Status
   *  There are two generic macros to Status (LIS_DISABLED and LIS_ENABLE)
   */
  void setEnableFIFO(char Status);

  /**
   * @fn void setEnableFIFOThreshold(char Status);
   *  @brief It allows enable the FIFO threshold
   *  @param Status
   *  There are two generic macros to Status (LIS_DISABLED and LIS_ENABLE)
   */
  void setEnableFIFOThreshold(char Status);

  /**
   * @fn void setFIFO_Mode(uint8_t FIFO);
   *  @brief It allows select the FIFO mode
   *  @param FIFO
   *  ----------------------------------
   *        Mode            |  FIFO
   *  ----------------------------------
   *       Bypass mode      |   0
   *        FIFO mode       |   32
   *   Stream-to-FIFO mode  |   64
   *  Bypass-to-Stream mode |   96
   *   Bypass-to-FIFO mode  |   224
   */
  void setFIFO_Mode(uint8_t FIFO);

  /**
   * @fn void setFIFO_Threshold(uint8_t Threshold);
   *  @brief It allows to set the FIFO threshold
   *  @param Threshold
   *  This threshold is the FIFO's deep with a maximum of 32.
   */
  void setFIFO_Threshold(uint8_t Threshold);

  /**
   * @fn void setINT2Empty(char Status);
   *  @brief It allows to drive the EMPTY signal on the INT2 pad.
   *  @param Status
   *  There are two generic macros to Status (LIS_DISABLED and LIS_ENABLE)
   *  EMPTY is high when there aren't values without read.
   */
  void setINT2Empty(char Status);

  /**
   * @fn void setINT1Ovr(char Status);
   *  @brief It allows to drive the OVR signal on the INT1 pad.
   *  @param Status
   *  There are two generic macros to Status (LIS_DISABLED and LIS_ENABLE)
   *  OVR is high when FIFO buffer is full.
   */
  void setINT1Ovr(char Status);

  /**
   * @fn void setIntFTH(char Status, char INT);
   *  @brief It allows to drive the FTH signal on the INT1 or/and INT2 pad.
   *  @param Status
   *  @param INT
   *  There are two generic macros to Status (LIS_DISABLED and LIS_ENABLE) and
   *  two specific macros to INT (INT1 and INT2) Ovr is high when FIFO buffer is
   *  full.
   *  FTH is high when the measure's values are higher than FIFO threshold.
   */
  void setIntFTH(char Status, char INT);

  /**
   * @fn uint8_t getFTH();
   *  @brief It allows to read the FTH signal
   *  @return FTH
   *  FTH is high when the measure's values are higher than FIFO threshold.
   */
  uint8_t getFTH();

  /**
   * @fn uint8_t getOVR();
   *  @brief It allows to read the OVR signal
   *  @return OVR
   *  OVR is high when FIFO buffer is full.
   */
  uint8_t getOVR();

  /**
   * @fn uint8_t getEMPTY();
   *  @brief It allows to read the EMPTY signal
   *  @return EMPTY
   *  EMPTY is high when there aren't values without read.
   */
  uint8_t getEMPTY();

  /**
   * @fn uint8_t getFSS();
   *  @brief It allows to read the FSS signal
   *  @return FSS
   *  The current number of unread samples stored in the FIFO buffer.
   */
  uint8_t getFSS();

  /***************************************************************************
   *                                  STATUS
   **************************************************************************/

  /**
   * @fn uint8_t getZYXOR();
   *  @brief X, Y, Z axis data overun
   *  @return ZYXOR
   *  1 -> A new set of data has overwritten the previous set
   */
  uint8_t getZYXOR();

  /**
   * @fn uint8_t getZOR();
   *  @brief Z axis data overun
   *  @return ZOR
   *  1 -> A new data for the Z axis has overwritten the previous set
   */
  uint8_t getZOR();

  /**
   * @fn uint8_t getYOR();
   *  @brief Y axis data overun
   *  @return YOR
   *  1 -> A new data for the Y axis has overwritten the previous set
   */
  uint8_t getYOR();

  /**
   * @fn uint8_t getXOR();
   *  @brief X axis data overun
   *  @return XOR
   *  1 -> A new data for the X axis has overwritten the previous set
   */
  uint8_t getXOR();

  /**
   * @fn uint8_t getZYXDA();
   *  @brief X, Y, Z axis new data available
   *  @return ZYXDA
   *  1 -> A new set of data is available
   */
  uint8_t getZYXDA();

  /**
   * @fn uint8_t getZDA();
   *  @brief Z axis new data available
   *  @return ZDA
   *  1 -> A new data for the Z axis is available
   */
  uint8_t getZDA();

  /**
   * @fn uint8_t getYDA();
   *  @brief Y axis new data available
   *  @return YDA
   *  1 -> A new data for the Y axis is available
   */
  uint8_t getYDA();

  /**
   * @fn uint8_t getXDA();
   *  @brief X axis new data available
   *  @return XDA
   *  1 -> A new data for the X axis is available
   */
  uint8_t getXDA();

  /***************************************************************************
   *                                TEMPERATURE
   **************************************************************************/

  /**
   * @fn float getTemp();
   *  @brief Temperature data
   *  @return temperature
   */
  float getTemp();

 private:
  uint8_t readRegister(uint8_t regis);
  void readAccel(float* x0, float* y0, float* z0);
  void writeRegister(uint8_t val, uint8_t regis, uint8_t bt);
  char readbit(uint8_t regis, int loc);
  float convert(int g, int axis);
  char exists(uint8_t* array, uint8_t value, int size);
  uint16_t referenceConvert(float axis);
  void writeReference(uint16_t x, uint16_t y, uint16_t z);

  unsigned long movingTime = 0;
  unsigned long movingTime10;
  unsigned long prevMovingTime = 0;
  unsigned long diff;
  unsigned long time1;
  unsigned long time2;
  unsigned long time3;
};

#endif