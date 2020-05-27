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

#define I2C_MODE 0
#define SPI_MODE 1

#define WIRE4 0
#define WIRE3 1

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
#define LIS_ENABLE 1
#define LIS_DISABLED 0
#define IG1 1
#define IG2 2
#define INT1 1
#define INT2 2
#define PP 0
#define OD 1
#define HINT 1
#define LINT 0
#define ENABLE_INT1 1
#define ENABLE_INT2 1
#define DISABLED_INT1 0
#define DISABLED_INT2 0
#define CHANGEALPF 0
#define NOCHANGEALPF 1
#define OFFDLPF 0
#define ONDLPF 1
#define ONDHPF 1

class LIS2HH12 {
 public:
  //*******Constructor*******
  LIS2HH12();
  uint8_t commInterface;
  uint8_t chipSelectPin;
  uint8_t I2CAddress;
  char SPI_Wire;
  float zerox, zeroy, zeroz;

  /***************************************************************************
   *                          Initialization
   **************************************************************************/

  /** @fn void begin(char Mode);
   *  @brief Set the basic to run the sensor
   *  @param mode You need to chose SPI or I2C
   */
  void begin(char Mode);
  /** @fn void setSPI(uint8_t csPin, char SPI_WIRE);
   *  @brief Set the CS and the Wire
   *  @param cdPin
   *  @param SPI_WIRE
   */
  void setSPI(uint8_t csPin, char SPI_WIRE);
  /** @fn void setI2C(uint8_t Address);
   *  @brief Change the I2C address
   *  @param Address
   */
  void setI2C(uint8_t Address);

  /***************************************************************************
   *                          Basic function
   **************************************************************************/

  /** @fn void setBasicConfig()
   *  @brief Set the basic to run the sensor
   */
  void setBasicConfig();

  /***************************************************************************
   *                          Apliccation
   **************************************************************************/

  /** @fn char getIsMoving();
   *  @brief return true if the sensor is moving
   */
  char getIsMoving();
  /** @fn float getActiveTime();
   *  @brief return a time moving value
   */
  float getActiveTime();

  /***************************************************************************
   *                          Operating Modes
   **************************************************************************/

  /** @fn void setFrequency(uint8_t ODR);
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
  /** @fn void setAxis(uint8_t ZYX);
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
  /** @fn setDLPF(char DLPF);
   *  @brief set digital low pass filter
   *  Default mode is OFFDLPF. if you use ONDLPF, you can't use decimator
   *  @param DLPF switch binary value
   *  There are two specific macros: ONDLPF and OFFDLPF
   */
  void setDLPF(char DLPF);
  /** @fn void setALPF(char ALPF);
   *  @brief set the analog low pass filter
   *  The analog ALPF have a default condition bandwidth of ODR/2 if you
   *  don't set the ALPF variable.
   *  @param ALPF switch binary value
   * There are two specific macros: NOCHANGEALPF and CHANGEALPF
   */
  void setALPF(char ALPF);
  /** @fn setanalogBandwidth(uint8_t BW);
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
  /** @fn setdigitalLPF(uint8_t LPFcutOff);
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
  /** @fn setActiveInactive(uint8_t threshold, uint8_t duration);
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
  /** @fn setPolarityINT(char H_Lint);
   *  @brief set the INT polarity
   *  The default polarity is HIGH
   *  @param H_Lint switch binary value
   *  There are two specifics macros for H_LINT: HINT and LINT
   */
  void setPolarityINT(char H_Lint);
  /** @fn void setFS(uint8_t FS);
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
  /** @fn setSelfTest(uint8_t mode);
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
  /** @fn setZeroLevel(float zx, float zy, float zz);
   *  @brief Function to set visually the zero level
   *  This function doesn't change nothing in the measure, it's only visual
   *  @param zx
   *  @param zy
   *  @param zz
   *  You choose the exact value for each axis
   */
  void setZeroLevel(float zx, float zy, float zz);
  /** @fn setInt2Boot(char Status);
   *  @brief set boot on the INT2 pad
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setInt2Boot(char Status);
  /** @fn setReboot();
   *  @brief Give the posible to reboot the code
   */
  void setReboot();
  /** @fn setDecimation(uint8_t Dec);
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
  /** @fn void setDebug(char Status);
   *  @brief set the debug mode
   *  You need to disabled the digital low pass filter (default mode)
   *  to use decimator
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setDebug(char Status);
  /** @fn void setSoftReset();
   *  @brief Give the posibility to do a reset
   */
  void setSoftReset();
  /** @fn setFDS(char OutData);
   *  @brief set the high pass filter(HPF) or the low pass filter (DLPF)
   *  You need to know that for use DLPF you have to select ONDLP in the
   * function setDLPF(char DLPF); Default value is decimator or DLPF
   *  @param OutData switch binary value
   *  There are two specific macros: ONDHPF and ONDLPF
   *  The accelerometer can't have DLPF and DHPF at the same time.
   */
  void setFDS(char OutData);
  /** @fn setBDU(char Status);
   *  @brief Block data update
   *  If the reading of the acceleration data is particularly slow and can't be
   *  synchronized with either the XYZDA bit or with DRDY signal, it's strongly
   *  recommended to set BDU
   *  @param Status switch binary value
   *  There are two generic macros for Status: LIS_DISABLED and LIS_DISABLED
   */
  void setBDU(char Status);

  /***************************************************************************
   *                   Modes Reading Accerlation Data
   **************************************************************************/

  char getAccelmG(float* x, float* y, float* z);
  void getAccelDataReadymG(float* x, float* y, float* z);
  void getAccelBDUmG(float* x, float* y, float* z);
  char getAccel(float* x, float* y, float* z);
  void getAccelDataReady(float* x, float* y, float* z);
  void getAccelBDU(float* x, float* y, float* z);
  void getAccelRAU(int* x, int* y, int* z);

  //******High Pass Filter******
  void setIntHPFData(uint8_t IntHPF);
  void setHPF(uint8_t HPF);

  void setCutOffHPF(uint8_t HPFcutOff);
  void setReference(uint16_t x, uint16_t y, uint16_t z);

  //*****Interrupt Generation*****
  void setIntGenerator1(char INT_1, char INT_2);
  void setIntGenerator2(char INT_1, char INT_2);

  //*****Inertial Interrupt*****
  void setIntMode(uint8_t IntMode, char IG);
  void setXYZIE(char Status, char IG);
  void setXIE(uint8_t XIE, char IG);
  void setYIE(uint8_t YIE, char IG);
  void setZIE(uint8_t ZIE, char IG);
  char getINT(char IG);
  void getAxisHInt(char* xh, char* yh, char* zh, char IG);
  void getAxisLInt(char* xl, char* yl, char* zl, char IG);
  void setMinDurationIG(uint8_t Duration, char IG);
  void setDecrementIG(char Status, char IG);
  void setWaitIG(char Status, char IG);
  // Interrupt generator 1 allows selecting a different threshold for
  // each axis while interrupt 2 supports the same threshold
  void setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z);
  void setThresholdIG2(uint8_t Threshold);
  void setLatchedIG(char Status, char IG);
  void setPP_OD(char PP_OD);
  // 6D is configured with setIntMode
  // If you want to use 4D, you need to set 6D also need to set Z axis to 0
  // and the next function (With the 4D mode you disabled Z axis)
  void set4Dmode(char Status, char IG);

  //************FIFO************
  void setEnableFIFO(char Status);
  void setEnableFIFOThreshold(char Status);
  void setFIFO_Mode(uint8_t FIFO);
  void setFIFO_Threshold(uint8_t Threshold);  // FIFO deep
  void setINT2Empty(char Status);
  void setINT1Ovr(char Status);
  void setIntFTH(char Status, char INT);
  char getFTH();
  char getOVR();
  char getEMPTY();
  char getFSS();

  //**********Status**********
  char getZYXOR();
  char getZOR();
  char getYOR();
  char getXOR();
  char getZYXDA();
  char getZDA();
  char getYDA();
  char getXDA();

  //***********Temp**********
  float getTemp();

 private:
  uint8_t readRegister(uint8_t regis);
  void readAccel(float* x0, float* y0, float* z0);
  void writeRegister(uint8_t val, uint8_t regis, uint8_t bt);
  char readbit(uint8_t regis, int loc);
  float convert(int g, int axis);
  char exists(uint8_t* array, uint8_t value, int size);
};

#endif