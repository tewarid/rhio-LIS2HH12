#include <rhioJF-LIS2HH12.h>

//*******Constructor*******
LIS2HH12::LIS2HH12() {
  chipSelectPin = 2;  // Choose the value
  I2CAddress = 0x1D;
  commInterface = I2C_MODE;
  SPI_Wire = WIRE4;
  zerox = 0;
  zeroy = 0;
  zeroz = 0;
}

//******Initialization******
void LIS2HH12::begin(char Mode) {
  commInterface = Mode;
  switch (commInterface) {
    case I2C_MODE:
      Wire.begin();
      break;
    case SPI_MODE:
      writeRegister(2, LIS2HH12_CTRL4, 253);
      SPI.begin();
      pinMode(chipSelectPin, OUTPUT);
      digitalWrite(chipSelectPin, HIGH);
      break;
    default:
      break;
  }
}
void LIS2HH12::setSPI(uint8_t csPin, char SPI_WIRE) {
  chipSelectPin = csPin;
  SPI_Wire = SPI_WIRE;
  if (SPI_Wire == WIRE3) {
    writeRegister(1, LIS2HH12_CTRL4, 254);
  }
}

void LIS2HH12::setI2C(uint8_t Address) { I2CAddress = Address; }

void LIS2HH12::setBasicConfig() {
  writeRegister(23, LIS2HH12_CTRL1, 232);
  writeRegister(0, LIS2HH12_CTRL3, 0);
  writeRegister(0, LIS2HH12_ACT_THS, 0);
  writeRegister(0, LIS2HH12_ACT_DUR, 0);
  writeRegister(0, LIS2HH12_FIFO_CTRL, 0);
}

//******Operating Modes******
/*-----------------------------------------------------------------------------
 *  Frequency |   ODR   |  BW=400 Hz  |  BW=200 Hz  |  BW=100 Hz  |  BW=50 Hz
 * ----------------------------------------------------------------------------
 *                      |                   Discarded samples
 * ----------------------------------------------------------------------------
 *   800 Hz   |   96    |      1      |      4      |      7      |     14
 *   400 Hz   |   80    |      1      |      1      |      4      |     7
 *   200 Hz   |   64    |      1      |      1      |      1      |     4
 *   100 Hz   |   48    |      1      |      1      |      1      |     1
 *   50  Hz   |   32    |      1      |      -      |      -      |     -
 *   10  Hz   |   16    |      1      |      -      |      -      |     -
 * Power Down |    0    |             |             |             |
 */
void LIS2HH12::setFrequency(uint8_t ODR) {
  writeRegister(ODR, LIS2HH12_CTRL1, 143);
}

/*-----------------------
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
void LIS2HH12::setAxis(uint8_t ZYX) { writeRegister(ZYX, LIS2HH12_CTRL1, 248); }

void LIS2HH12::setLPFilters(char analogLPF, char digitalLPF) {  // Revisar
  writeRegister(0, LIS2HH12_CTRL4, 247);
  if (analogLPF == 1) {
    writeRegister(8, LIS2HH12_CTRL4, 247);
  }
  writeRegister(0, LIS2HH12_CTRL1, 127);
  if (digitalLPF == 1) {
    writeRegister(128, LIS2HH12_CTRL1, 127);
  }
}

/*-----------------------
 *   (BW)Hz |    BW
 * ----------------------
 *    400   |    0
 *    200   |    64
 *    100   |    128
 *    50    |    192
 */
void LIS2HH12::setanalogBandwidth(uint8_t BW) {
  writeRegister(BW, LIS2HH12_CTRL4, 63);
}

/*-----------------------
 * (Cut off)Hz | LPFcutOff
 * ----------------------
 *    ODR/50   |    0
 *    ODR/100  |    32
 *    ODR/9    |    64
 *    ODR/200  |    96
 */
void LIS2HH12::setdigitalLPF(uint8_t LPFcutOff) {  // Mismo registro que HPF?
  writeRegister(LPFcutOff, LIS2HH12_CTRL2, 159);
}

/*---------------------------------------
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
// The threshold is represented by 7 bits bit [6:0], bit7 must be set to 0
// The duration is represented by 8 bits
void LIS2HH12::setActiveInactive(uint8_t threshold, uint8_t duration) {
  writeRegister(threshold, LIS2HH12_ACT_THS, 0);
  writeRegister(duration, LIS2HH12_ACT_DUR, 0);
  writeRegister(32, LIS2HH12_CTRL3, 223);
}

void LIS2HH12::setIntDataready(char IntDataReady, char INT) {
  if (INT == 1) {
    writeRegister(0, LIS2HH12_CTRL3, 254);
    if (IntDataReady == 1) {
      writeRegister(1, LIS2HH12_CTRL3, 254);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL6, 254);
    if (IntDataReady == 1) {
      writeRegister(1, LIS2HH12_CTRL6, 254);
    }
  }
}

void LIS2HH12::setPolarityINT(char H_Lint) {
  writeRegister(2, LIS2HH12_CTRL5, 253);
}

/*----------------------------------
 *   +/- g  |   Sensitivity  |  FS
 * ---------------------------------
 *     2    |      0.061     |  0
 *     4    |      0.122     |  32
 *     8    |      0.244     |  48
 */
void LIS2HH12::setFS(uint8_t FS) { writeRegister(FS, LIS2HH12_CTRL4, 207); }

/*----------------------------------------
 *        Action            |   mode
 * ---------------------------------------
 *      Normal mode         |    0
 *  Positive sign self-test |    4
 *  Negative sign self-test |    8
 */
void LIS2HH12::setSelfTest(uint8_t mode) {
  writeRegister(mode, LIS2HH12_CTRL5, 243);
}

void LIS2HH12::setZeroLevel(int zx, int zy, int zz) {
  zerox = zx;
  zeroy = zy;
  zeroz = zz;
}

void LIS2HH12::setInt2Boot(char Status) {
  writeRegister(0, LIS2HH12_CTRL6, 223);
  if (Status == 1) {
    writeRegister(32, LIS2HH12_CTRL6, 223);
  }
}

void LIS2HH12::setReboot() { writeRegister(128, LIS2HH12_CTRL6, 127); }

/*----------------------------------------
 *       Update accel       |   Dec
 * ---------------------------------------
 *      No decimation       |    0
 *     Every 2 samples      |    16
 *     Every 4 samples      |    32
 *     Every 8 samples      |    48
 */
void LIS2HH12::setDecimation(uint8_t Dec) {
  writeRegister(Dec, LIS2HH12_CTRL5, 207);
}

void LIS2HH12::setDebug(char Debug) {
  writeRegister(0, LIS2HH12_CTRL5, 127);
  if (Debug == 1) {
    writeRegister(128, LIS2HH12_CTRL5, 127);
  }
}

void LIS2HH12::setSoftReset() { writeRegister(64, LIS2HH12_CTRL5, 191); }

//******Modes Reading Acceleration Data******
char LIS2HH12::getAccelUsingStatus(int* x, int* y, int* z) {  // Revisar
  int x0, y0, z0;
  char ZYXDA, ZYXOR;
  char result = 0;
  ZYXDA = readbit(LIS2HH12_STATUS, 3);
  ZYXOR = readbit(LIS2HH12_STATUS, 7);
  if (ZYXDA == 1) {
    if (ZYXOR == 1) {
      result = 1;
    }
    readAccel(&x0, &y0, &z0);
    *x = x0;
    *y = y0;
    *z = z0;
  }
  return (result);
}

void LIS2HH12::getAccelUsingDataready(int* x, int* y, int* z) {
  int x0, y0, z0;
  char int1, int2, H_L, drdy_int1, drdy_int2;
  drdy_int1 = readbit(LIS2HH12_CTRL3, 0);
  drdy_int2 = readbit(LIS2HH12_CTRL6, 0);
  H_L = readbit(LIS2HH12_CTRL5, 1);
  int1 = readbit(LIS2HH12_IG_SRC1, 6);
  int2 = readbit(LIS2HH12_IG_SRC2, 6);
  H_L = ~H_L;  // NOT operator
  if (drdy_int1 == 1 && int1 == H_L) {
    readAccel(&x0, &y0, &z0);
    *x = x0;
    *y = y0;
    *z = z0;
  }
  if (drdy_int2 == 1 && int2 == H_L) {
    readAccel(&x0, &y0, &z0);
    *x = x0;
    *y = y0;
    *z = z0;
  }
}

void LIS2HH12::getAccelUsingBDU(int* x, int* y, int* z) {
  int x0, y0, z0;
  writeRegister(8, LIS2HH12_CTRL1, 247);
  readAccel(&x0, &y0, &z0);
  *x = x0;
  *y = y0;
  *z = z0;
}

void LIS2HH12::getAccelWithoutConvert(int* x, int* y, int* z) {
  uint8_t XL, XH, YL, YH, ZH, ZL;
  XL = readRegister(LIS2HH12_OUT_X_L);
  XH = readRegister(LIS2HH12_OUT_X_H);
  YL = readRegister(LIS2HH12_OUT_Y_L);
  YH = readRegister(LIS2HH12_OUT_Y_H);
  ZL = readRegister(LIS2HH12_OUT_Z_L);
  ZH = readRegister(LIS2HH12_OUT_Z_H);
  *x = XH << 8 | XL;
  *y = YH << 8 | YL;
  *z = ZH << 8 | ZL;
}

//******High Pass Filter******
/*-------------------------------
 *   INT1   |   INT2   |  IntHPF
 * ------------------------------
 *   data   |   data   |    0
 *   data   |  dataHPF |    1
 *  dataHPF |   data   |    2
 *  dataHPF |  dataHPF |    3
 */
void LIS2HH12::setIntHPFData(uint8_t IntHPF) {
  writeRegister(IntHPF, LIS2HH12_CTRL2, 252);
}

/*-------------------------------
 *        Mode        |   HPF
 * ------------------------------
 *       Normal       |   0
 *   Reference signal |   8
 */
void LIS2HH12::setHPF(uint8_t HPF) { writeRegister(HPF, LIS2HH12_CTRL2, 231); }

void LIS2HH12::setFDS(uint8_t OutData) {
  if (OutData == 1) {
    writeRegister(4, LIS2HH12_CTRL2, 251);
  } else {
    writeRegister(0, LIS2HH12_CTRL2, 251);
  }
}

/*-----------------------
 * (Cut off)Hz | HPFcutOff
 * ----------------------
 *    ODR/50   |    0
 *    ODR/100  |    32
 *    ODR/9    |    64
 *    ODR/200  |    96
 */
void LIS2HH12::setCutOffHPF(uint8_t HPFcutOff) {
  writeRegister(HPFcutOff, LIS2HH12_CTRL2, 159);
}

void LIS2HH12::setReference(uint16_t x, uint16_t y, uint16_t z) {
  uint8_t XLR, XHR, YLR, YHR, ZHR, ZLR;
  XLR = x & 255;
  XHR = x >> 8 & 255;
  YLR = y & 255;
  YHR = y >> 8 & 255;
  ZLR = z & 255;
  ZHR = z >> 8 & 255;
  writeRegister(XLR, LIS2HH12_XL_REFERENCE, 0);
  writeRegister(XHR, LIS2HH12_XH_REFERENCE, 0);
  writeRegister(YLR, LIS2HH12_YL_REFERENCE, 0);
  writeRegister(YHR, LIS2HH12_YH_REFERENCE, 0);
  writeRegister(ZLR, LIS2HH12_ZL_REFERENCE, 0);
  writeRegister(ZHR, LIS2HH12_ZH_REFERENCE, 0);
}

//*****Interrupt Generation*****
void LIS2HH12::setIntGenerator1(char INT1, char INT2) {
  writeRegister(0, LIS2HH12_CTRL3, 247);
  if (INT1 == 1) {
    writeRegister(8, LIS2HH12_CTRL3, 247);
  }
  writeRegister(0, LIS2HH12_CTRL6, 247);
  if (INT2 == 1) {
    writeRegister(8, LIS2HH12_CTRL6, 247);
  }
}

void LIS2HH12::setIntGenerator2(char INT1, char INT2) {
  writeRegister(0, LIS2HH12_CTRL3, 239);
  if (INT1 == 1) {
    writeRegister(16, LIS2HH12_CTRL3, 239);
  }
  writeRegister(0, LIS2HH12_CTRL6, 239);
  if (INT2 == 1) {
    writeRegister(16, LIS2HH12_CTRL6, 239);
  }
}

//*****Inertial Interrupt*****
/*-------------------------------------------------
 *                Mode                |  IntMode
 * ------------------------------------------------
 *   OR combination of axis requests  |    0
 *   6-direction movement recognition |    64
 *   AND combination of axis requests |    128
 *   6-direction position recognition |    192
 */
void LIS2HH12::setIntMode(uint8_t IntMode,
                          char IG) {  // IG = 0 is IG1 and IG = 1  is IG2
  if (IG == 1) {
    writeRegister(IntMode, LIS2HH12_IG_CFG1, 63);
  } else {
    writeRegister(IntMode, LIS2HH12_IG_CFG2, 63);
  }
}

void LIS2HH12::setAllAxis(char Axis, char IG) {
  if (IG == 1) {
    writeRegister(0, LIS2HH12_IG_CFG1, 192);
    if (Axis == 1) {
      writeRegister(63, LIS2HH12_IG_CFG1, 192);
    }
  } else {
    writeRegister(0, LIS2HH12_IG_CFG2, 192);
    if (Axis == 1) {
      writeRegister(63, LIS2HH12_IG_CFG2, 192);
    }
  }
}

/*-------------------
 * XHIE | XLIE | XIE
 *--------------------
 *  0   |  0   |  0
 *  0   |  1   |  1
 *  1   |  0   |  2
 *  1   |  1   |  3
 */
void LIS2HH12::setXIE(uint8_t XIE, char IG) {
  if (IG == 1) {
    writeRegister(XIE, LIS2HH12_IG_CFG1, 252);
  } else {
    writeRegister(XIE, LIS2HH12_IG_CFG2, 252);
  }
}

/*-------------------
 * YHIE | YLIE | YIE
 *--------------------
 *  0   |  0   |  0
 *  0   |  1   |  4
 *  1   |  0   |  8
 *  1   |  1   |  12
 */
void LIS2HH12::setYIE(uint8_t YIE, char IG) {
  if (IG == 1) {
    writeRegister(YIE, LIS2HH12_IG_CFG1, 243);
  } else {
    writeRegister(YIE, LIS2HH12_IG_CFG2, 243);
  }
}

/*-------------------
 * ZHIE | ZLIE | ZIE
 *--------------------
 *  0   |  0   |  0
 *  0   |  1   |  16
 *  1   |  0   |  32
 *  1   |  1   |  48
 */
void LIS2HH12::setZIE(uint8_t ZIE, char IG) {
  if (IG == 1) {
    writeRegister(ZIE, LIS2HH12_IG_CFG1, 207);
  } else {
    writeRegister(ZIE, LIS2HH12_IG_CFG2, 207);
  }
}

char LIS2HH12::getINT(char IG) {
  char INTG;
  if (IG == 1) {
    INTG = readbit(LIS2HH12_IG_SRC1, 6);
  } else {
    INTG = readbit(LIS2HH12_IG_SRC2, 6);
  }
  return (INTG);
}

void LIS2HH12::getAxisHInt(char* xh, char* yh, char* zh, char IG) {
  if (IG == 1) {
    *xh = readbit(LIS2HH12_IG_SRC1, 1);
    *yh = readbit(LIS2HH12_IG_SRC1, 3);
    *zh = readbit(LIS2HH12_IG_SRC1, 5);
  } else {
    *xh = readbit(LIS2HH12_IG_SRC2, 1);
    *yh = readbit(LIS2HH12_IG_SRC2, 3);
    *zh = readbit(LIS2HH12_IG_SRC2, 5);
  }
}

void LIS2HH12::getAxisLInt(char* xl, char* yl, char* zl, char IG) {
  if (IG == 1) {
    *xl = readbit(LIS2HH12_IG_SRC1, 0);
    *yl = readbit(LIS2HH12_IG_SRC1, 2);
    *zl = readbit(LIS2HH12_IG_SRC1, 4);
  } else {
    *xl = readbit(LIS2HH12_IG_SRC2, 0);
    *yl = readbit(LIS2HH12_IG_SRC2, 2);
    *zl = readbit(LIS2HH12_IG_SRC2, 4);
  }
}

/*---------------------------------------
 *      ODR    | Duration LSB value (ms)
 * --------------------------------------
 *      800    |        1.25
 *      400    |        2.5
 *      200    |        5
 *      100    |        10
 *      50     |        20
 *      10     |        100
 * The duration is represented by 7 bits DUR[6:0]
 * Duration time is measured in N/ODR, where N is the duration
 * register content
 */
void LIS2HH12::setMinDurationINT(uint8_t Duration,
                                 char IG) {  // Revisar info datasheet
  if (IG == 1) {
    writeRegister(Duration, LIS2HH12_IG_DUR1, 128);
  } else {
    writeRegister(Duration, LIS2HH12_IG_DUR2, 128);
  }
}

void LIS2HH12::setDecrementINT(char Status, char IG) {
  if (IG == 1) {
    writeRegister(0, LIS2HH12_CTRL7, 239);
    if (Status == 1) {
      writeRegister(16, LIS2HH12_CTRL7, 239);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL7, 239);
    if (Status == 1) writeRegister(32, LIS2HH12_CTRL7, 223);
  }
}

void LIS2HH12::setWaitINT(char Status, char IG) {
  if (IG == 1) {
    writeRegister(0, LIS2HH12_CTRL7, 127);
    if (Status == 1) {
      writeRegister(128, LIS2HH12_CTRL7, 127);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL7, 127);
    if (Status == 1) writeRegister(128, LIS2HH12_CTRL7, 127);
  }
}

/* ---------------------------------------
 *  Full scale | Threshold LSB value (mg)
 * --------------------------------------
 *      2      |           8
 *      4      |           16
 *      8      |           31
 *---------------------------------------
 *The threshold is represented by 8 bits
 */
void LIS2HH12::setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z) {
  writeRegister(X, LIS2HH12_IG_THS_X1, 0);
  writeRegister(Y, LIS2HH12_IG_THS_Y1, 0);
  writeRegister(Z, LIS2HH12_IG_THS_Z1, 0);
}

void LIS2HH12::setThresholdIG2(uint8_t Threshold) {
  writeRegister(Threshold, LIS2HH12_IG_THS2, 0);
}

void LIS2HH12::setLatchedINT(char Status, char IG) {
  if (IG == 1) {
    writeRegister(0, LIS2HH12_CTRL7, 251);
    if (Status == 1) {
      writeRegister(4, LIS2HH12_CTRL7, 251);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL7, 247);
    if (Status == 1) {
      writeRegister(8, LIS2HH12_CTRL7, 247);
    }
  }
}

void LIS2HH12::setPP_OD(char PP_OD) {
  writeRegister(0, LIS2HH12_CTRL5, 254);
  if (PP_OD == 1) {
    writeRegister(1, LIS2HH12_CTRL5, 254);
  }
}

//****6D/4D Orientation Detection****
void LIS2HH12::set4Dmode(char Status, char IG) {
  if (IG == 1) {
    writeRegister(0, LIS2HH12_CTRL5, 254);
    if (Status == 1) {
      writeRegister(1, LIS2HH12_CTRL5, 254);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL5, 253);
    if (Status == 1) {
      writeRegister(2, LIS2HH12_CTRL5, 253);
    }
  }
}

//************FIFO************
void LIS2HH12::setFIFO_EN(char Status) {
  writeRegister(0, LIS2HH12_CTRL3, 127);
  if (Status == 1) {
    writeRegister(128, LIS2HH12_CTRL3, 127);
  }
}

void LIS2HH12::setFIFO_ENthreshold(char Status) {
  writeRegister(0, LIS2HH12_CTRL3, 191);
  if (Status == 1) {
    writeRegister(64, LIS2HH12_CTRL3, 191);
  }
}

/*----------------------------------
 *        Mode            |  FIFO
 *----------------------------------
 *       Bypass mode      |   0
 *        FIFO mode       |   32
 *   Stream-to-FIFO mode  |   64
 *  Bypass-to-Stream mode |   96
 *   Bypass-to-FIFO mode  |   224
 */
void LIS2HH12::setFIDO_Mode(uint8_t FIFO) {
  writeRegister(FIFO, LIS2HH12_FIFO_CTRL, 31);
}

void LIS2HH12::setFIFO_Threshold(uint8_t Threshold) {
  uint8_t Threshold1;
  Threshold1 = Threshold - 1;
  writeRegister(Threshold1, LIS2HH12_FIFO_CTRL, 224);
}

char LIS2HH12::getFTH() {
  char FTH;
  FTH = readbit(LIS2HH12_FIFO_SRC, 7);
  return (FTH);
}

char LIS2HH12::getOVR() {
  char OVR;
  OVR = readbit(LIS2HH12_FIFO_SRC, 6);
  return (OVR);
}

char LIS2HH12::getEMPTY() {
  char EMPTY;
  EMPTY = readbit(LIS2HH12_FIFO_SRC, 5);
  return (EMPTY);
}

char LIS2HH12::getFSS() {
  char FSS;
  uint8_t read;
  read = readRegister(LIS2HH12_FIFO_SRC);
  FSS = read & 31;
  FSS += 1;
  return (FSS);
}

void LIS2HH12::setINT2Empty(char Status) {
  writeRegister(0, LIS2HH12_CTRL6, 251);
  if (Status == 1) {
    writeRegister(4, LIS2HH12_CTRL6, 251);
  }
}

void LIS2HH12::setINT1Ovr(char Status) {
  writeRegister(0, LIS2HH12_CTRL3, 251);
  if (Status == 1) {
    writeRegister(4, LIS2HH12_CTRL3, 251);
  }
}

void LIS2HH12::setIntFTH(char Status, char INT) {
  if (INT == 1) {
    writeRegister(0, LIS2HH12_CTRL3, 253);
    if (Status == 1) {
      writeRegister(2, LIS2HH12_CTRL3, 253);
    }
  } else {
    writeRegister(0, LIS2HH12_CTRL6, 253);
    if (Status == 1) {
      writeRegister(2, LIS2HH12_CTRL6, 253);
    }
  }
}

//**********Status**********
char LIS2HH12::getZYXOR() {
  char ZYXOR;
  ZYXOR = readbit(LIS2HH12_STATUS, 7);
  return (ZYXOR);
}

char LIS2HH12::getZOR() {
  char ZOR;
  ZOR = readbit(LIS2HH12_STATUS, 6);
  return (ZOR);
}

char LIS2HH12::getYOR() {
  char YOR;
  YOR = readbit(LIS2HH12_STATUS, 5);
  return (YOR);
}

char LIS2HH12::getXOR() {
  char XOR;
  XOR = readbit(LIS2HH12_STATUS, 4);
  return (XOR);
}

char LIS2HH12::getZYXDA() {
  char ZYXDA;
  ZYXDA = readbit(LIS2HH12_STATUS, 3);
  return (ZYXDA);
}

char LIS2HH12::getZDA() {
  char ZDA;
  ZDA = readbit(LIS2HH12_STATUS, 2);
  return (ZDA);
}

char LIS2HH12::getYDA() {
  char YDA;
  YDA = readbit(LIS2HH12_STATUS, 1);
  return (YDA);
}

char LIS2HH12::getXDA() {
  char XDA;
  XDA = readbit(LIS2HH12_STATUS, 0);
  return (XDA);
}

//***********Temp**********
uint16_t LIS2HH12::getTemp() {
  uint8_t TEMP_L, TEMP_H;
  uint16_t TEMP;
  TEMP_L = readRegister(LIS2HH12_TEMP_L);
  TEMP_H = readRegister(LIS2HH12_TEMP_H);
  TEMP_H = TEMP_H << 8;
  TEMP = TEMP_H | TEMP_L;
  TEMP = TEMP * 0.125;
  return (TEMP);
}

//*************************UTILITY*************************//
uint8_t LIS2HH12::readRegister(uint8_t regis) {
  uint8_t result = 0;
  uint8_t bytes = 1;
  switch (commInterface) {
    case I2C_MODE:
      Wire.beginTransmission(I2CAddress);
      Wire.write(regis);
      Wire.endTransmission();
      Wire.requestFrom(I2CAddress, bytes);
      while (Wire.available()) {
        result = Wire.read();
      }
      break;
    case SPI_MODE:  // Revisar
      SPI.beginTransaction(
          SPISettings(LIS2HH12_SPI_CLOCK, MSBFIRST, LIS2HH12_SPI_MODE));
      digitalWrite(chipSelectPin, LOW);
      result = SPI.transfer(regis);
      digitalWrite(chipSelectPin, HIGH);
      SPI.endTransaction();
      break;
    default:
      break;
  }
  return result;
}

void LIS2HH12::writeRegister(uint8_t val, uint8_t regis, uint8_t bt) {
  // bt is a invert binary variable, with it you choose the bits
  // that you want read and change to cero
  uint8_t read, result, val2;
  read = readRegister(regis);
  result = read & bt;
  val2 = result | val;
  switch (commInterface) {
    case I2C_MODE:
      Wire.beginTransmission(I2CAddress);
      Wire.write(regis);
      Wire.write(val2);
      Wire.endTransmission();
      break;

    case SPI_MODE:  // Revisar
      SPI.beginTransaction(
          SPISettings(LIS2HH12_SPI_CLOCK, MSBFIRST, LIS2HH12_SPI_MODE));
      digitalWrite(chipSelectPin, LOW);
      SPI.transfer(regis);
      SPI.transfer(val2);
      digitalWrite(chipSelectPin, HIGH);
      SPI.endTransaction();
      break;
    default:
      break;
  }
}

void LIS2HH12::readAccel(int* x0, int* y0, int* z0) {
  uint8_t XL, XH, YL, YH, ZH, ZL;
  int x01, y01, z01;
  char FS1, FS0;
  XL = readRegister(LIS2HH12_OUT_X_L);
  XH = readRegister(LIS2HH12_OUT_X_H);
  YL = readRegister(LIS2HH12_OUT_Y_L);
  YH = readRegister(LIS2HH12_OUT_Y_H);
  ZL = readRegister(LIS2HH12_OUT_Z_L);
  ZH = readRegister(LIS2HH12_OUT_Z_H);
  FS1 = readbit(LIS2HH12_CTRL4, 5);
  FS0 = readbit(LIS2HH12_CTRL4, 4);
  x01 = XH << 8 | XL;
  y01 = YH << 8 | YL;
  z01 = ZH << 8 | ZL;
  if (FS1 == 0 && FS0 == 0) {
    *x0 = convert(2, x01) + zerox;
    *y0 = convert(2, y01) + zeroy;
    *z0 = convert(2, z01) + zeroz;
  }
  if (FS1 == 1 && FS0 == 0) {
    *x0 = convert(4, x01) + zerox;
    *y0 = convert(4, y01) + zeroy;
    *z0 = convert(4, z01) + zeroz;
  }
  if (FS1 == 1 && FS0 == 1) {
    *x0 = convert(8, x01) + zerox;
    *y0 = convert(8, y01) + zeroy;
    *z0 = convert(8, z01) + zeroz;
  }
}

int LIS2HH12::convert(int g, int axis) {
  if (axis <= 32787) {
    if (g == 2) {
      axis = axis * 0.061;
    }
    if (g == 4) {
      axis = axis * 0.122;
    }
    if (g == 8) {
      axis = axis * 0.244;
    }
  } else {
    int axis0;
    if (g == 2) {
      axis0 = (axis * 0.065) - 2131;
      axis = axis0 - 2131;
    }
    if (g == 4) {
      axis0 = (axis * 0.122) - 4000;
      axis = axis0 - 4000;
    }
    if (g == 8) {
      axis0 = (axis * 0.244) - 8000;
      axis = axis0 - 8000;
    }
  }
  return axis;
}

char LIS2HH12::readbit(uint8_t regis, int loc) {
  uint8_t val;
  char bit;
  val = readRegister(regis);
  val = val >> loc;
  bit = val & 1;
  return bit;
}
