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
#define ONHPF 1
#define ONLPF 1

class LIS2HH12 {
 public:
  //*******Constructor*******
  LIS2HH12();
  uint8_t commInterface;
  uint8_t chipSelectPin;
  uint8_t I2CAddress;
  char SPI_Wire;
  float zerox, zeroy, zeroz;

  //******Initialization******
  void begin(char Mode);
  void setSPI(uint8_t csPin, char SPI_WIRE);
  void setI2C(uint8_t Address);

  //******Basic function******
  void setBasicConfig();

  //*******Apliccation*******
  char getIsMoving();
  float getActiveTime();

  //******Operating Modes******
  // There are a decimation filter cutoff frequency that depend of ODR
  void setFrequency(uint8_t ODR);
  void setAxis(uint8_t ZYX);
  void setDLPF(char DLPF);
  // The analog LPF have a default condition bandwidth of ODR/2 if you
  // don't set the ALPF variable
  void setALPF(char ALPF);
  void setanalogBandwidth(uint8_t BW);
  void setdigitalLPF(uint8_t LPFcutOff);
  void setActiveInactive(uint8_t threshold, uint8_t duration);
  void setIntDataready(char Status, char INT);
  void setPolarityINT(char H_Lint);
  void setFS(uint8_t FS);
  void setSelfTest(uint8_t mode);
  void setZeroLevel(float zx, float zy, float zz);
  void setInt2Boot(char Status);
  void setReboot();
  void setDecimation(uint8_t Dec);
  void setDebug(char Status);
  void setSoftReset();
  void setFDS(char OutData);
  void setBDU(char Status);

  //******Modes Reading Accerlation Data******
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