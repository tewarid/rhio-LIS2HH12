/**
 * Rhomb.io LIS2HH12 library
 *
 * @author Jose Francisco Martí Martín
 * @version 0.1.0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include "rhio-LIS2HH12.h"

//*******Constructor*******

LIS2HH12::LIS2HH12() {
  I2CAddress = 0x1D;
  zerox = 0;
  zeroy = 0;
  zeroz = 0;
}

//******Initialization******

void LIS2HH12::begin() {
  Wire.begin();
  setSoftReset();
}

void LIS2HH12::setI2C(uint8_t Address) { I2CAddress = Address; }

//******Basic function******

void LIS2HH12::setBasicConfig() {
  writeRegister(23, LIS2HH12_CTRL1, 232);
  writeRegister(0, LIS2HH12_CTRL2, 255);
  writeRegister(0, LIS2HH12_CTRL3, 0);
  writeRegister(0, LIS2HH12_ACT_THS, 0);
  writeRegister(0, LIS2HH12_ACT_DUR, 0);
  writeRegister(0, LIS2HH12_FIFO_CTRL, 0);
}

//*******Apliccation*******

uint8_t LIS2HH12::getIsMoving() {
  uint8_t xh, yh, zh;
  uint8_t ctrl4, FSS, value = 0, valuez = 0;
  setXIE(2, IG1);
  setYIE(8, IG1);
  setZIE(32, IG1);
  setMinDurationIG(0, IG1);
  ctrl4 = readRegister(LIS2HH12_CTRL4);
  ctrl4 = ctrl4 >> 4;
  FSS = ctrl4 & 11;
  switch (FSS) {
    case 00:              // 2g
      value = 208 / 8;    // 208 mg
      valuez = 1208 / 8;  // 1208 mg
      break;
    case 10:               // 4g
      value = 208 / 16;    // 208 mg
      valuez = 1200 / 16;  // 1200 mg
      break;
    case 11:               // 8g
      value = 217 / 31;    // 217 mg
      valuez = 1209 / 31;  // 1209 mg
      break;
    default:
      break;
  }
  setThresholdIG1(value, value, valuez);
  getAxisHInt(&xh, &yh, &zh, IG1);
  if (this->prevMovingTime == 0 && xh == 0 && yh == 0 && zh == 0) {
    this->time1 = millis();
    this->time3 = millis();
  }
  if (xh == 1 || yh == 1 || zh == 1) {
    if (this->prevMovingTime == 0) {
      this->prevMovingTime = millis();
      this->time1 = millis();
      this->time2 = millis();
    }
    this->time1 = millis();
    this->movingTime10 = this->time1 - this->time2;
    diff = millis() - this->prevMovingTime;
    this->movingTime += diff;
    this->prevMovingTime = millis();
    StopTime = 0;
    this->time4 = millis();
    time3 = time4;
    return 1;
  }

  this->prevMovingTime = 0;
  this->movingTime = 0;
  this->movingTime10 = this->time1 - this->time2;
  this->StopTime = this->time3 - this->time4;

  if (this->time1 - time2 >= 600000) {
    this->time2 = millis();
    this->movingTime10 = 0;
  }
  return 0;
}

float LIS2HH12::getActiveTime() { return movingTime; }

float LIS2HH12::getTimeUntil10Min() { return movingTime10; }

float LIS2HH12::getStopTime() { return StopTime; }

//******Operating Modes******

void LIS2HH12::setFrequency(uint8_t ODR) {
  uint8_t array[7] = {0, 16, 32, 48, 64, 80, 96};
  if (!exists(array, ODR, 7)) {
    Serial.println("Wrong frequency value");
    return;
  }
  writeRegister(ODR, LIS2HH12_CTRL1, 143);
}

void LIS2HH12::setAxis(uint8_t ZYX) {
  uint8_t array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  if (!exists(array, ZYX, 8)) {
    Serial.println("Wrong axis value");
    return;
  }
  writeRegister(ZYX, LIS2HH12_CTRL1, 248);
}

void LIS2HH12::setDLPF(char DLPF) {
  if (DLPF == ONDLPF) {
    writeRegister(0, LIS2HH12_CTRL1, 127);
  }
  if (DLPF == OFFDLPF) {
    writeRegister(128, LIS2HH12_CTRL1, 127);
  }
}

void LIS2HH12::setALPF(char ALPF) {
  if (ALPF == NOCHANGEALPF) {
    writeRegister(0, LIS2HH12_CTRL4, 247);
  }
  if (ALPF == CHANGEALPF) {
    writeRegister(8, LIS2HH12_CTRL4, 247);
  }
}

void LIS2HH12::setanalogBandwidth(uint8_t BW) {
  uint8_t array[4] = {0, 64, 128, 192};
  if (!exists(array, BW, 4)) {
    Serial.println("Wrong bandwidth value");
    return;
  }
  writeRegister(BW, LIS2HH12_CTRL4, 63);
}

void LIS2HH12::setdigitalLPF(uint8_t LPFcutOff) {
  uint8_t array[4] = {0, 32, 64, 96};
  if (!exists(array, LPFcutOff, 4)) {
    Serial.println("Wrong cut off frequency value");
    return;
  }
  writeRegister(LPFcutOff, LIS2HH12_CTRL2, 159);
}

void LIS2HH12::setActiveInactive(uint8_t threshold, uint8_t duration) {
  if (threshold >= 128) {
    Serial.println("Threshold value is bigger than 127");
    return;
  }
  writeRegister(threshold, LIS2HH12_ACT_THS, 0);
  writeRegister(duration, LIS2HH12_ACT_DUR, 0);
  writeRegister(32, LIS2HH12_CTRL3, 223);
}

void LIS2HH12::setIntDataready(char Status, char INT) {
  if (INT == INT1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL3, 254);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(1, LIS2HH12_CTRL3, 254);
    }
  }
  if (INT == INT2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL6, 254);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(1, LIS2HH12_CTRL6, 254);
    }
  }
}

void LIS2HH12::setPolarityINT(char H_Lint) {
  if (H_Lint == HINT) {
    writeRegister(0, LIS2HH12_CTRL5, 253);
  }
  if (H_Lint == LINT) {
    writeRegister(2, LIS2HH12_CTRL5, 253);
  }
}

void LIS2HH12::setFS(uint8_t FS) {
  uint8_t array[4] = {0, 32, 48};
  if (!exists(array, FS, 4)) {
    Serial.println("Wrong full-scale value");
    return;
  }
  writeRegister(FS, LIS2HH12_CTRL4, 207);
}

void LIS2HH12::setSelfTest(uint8_t mode) {
  uint8_t array[3] = {0, 4, 8};
  if (!exists(array, mode, 3)) {
    Serial.println("Wrong self test value");
    return;
  }
  writeRegister(mode, LIS2HH12_CTRL5, 243);
}

void LIS2HH12::setZeroLevel(float zx, float zy, float zz) {
  zerox = zx;
  zeroy = zy;
  zeroz = zz;
}

void LIS2HH12::setInt2Boot(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL6, 223);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(32, LIS2HH12_CTRL6, 223);
  }
}

void LIS2HH12::setReboot() { writeRegister(128, LIS2HH12_CTRL6, 127); }

void LIS2HH12::setDecimation(uint8_t Dec) {
  uint8_t array[4] = {0, 16, 32, 48};
  if (!exists(array, Dec, 4)) {
    Serial.println("Wrong decimation value");
    return;
  }
  writeRegister(Dec, LIS2HH12_CTRL5, 207);
}

void LIS2HH12::setDebug(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL5, 127);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(128, LIS2HH12_CTRL5, 127);
  }
}

void LIS2HH12::setSoftReset() { writeRegister(64, LIS2HH12_CTRL5, 191); }

void LIS2HH12::setFDS(char OutData) {
  if (OutData == ONDHPF) {
    writeRegister(4, LIS2HH12_CTRL2, 251);
  }
  if (OutData == ONDLPF) {
    writeRegister(0, LIS2HH12_CTRL2, 251);
  }
}

void LIS2HH12::setBDU(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL1, 247);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(8, LIS2HH12_CTRL1, 247);
  }
}
//******Reading Acceleration Data Modes ******

uint8_t LIS2HH12::getAccelmG(float* x, float* y, float* z) {
  float x0, y0, z0;
  char ZYXDA, ZYXOR;
  uint8_t result = 0;
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

void LIS2HH12::getAccelDataReadymG(float* x, float* y, float* z) {
  float x0, y0, z0;
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

void LIS2HH12::getAccelBDUmG(float* x, float* y, float* z) {
  float x0, y0, z0;
  writeRegister(8, LIS2HH12_CTRL1, 247);
  readAccel(&x0, &y0, &z0);
  *x = x0;
  *y = y0;
  *z = z0;
}

uint8_t LIS2HH12::getAccel(float* x, float* y, float* z) {
  float x0, y0, z0;
  char ZYXDA, ZYXOR;
  uint8_t result = 0;
  ZYXDA = readbit(LIS2HH12_STATUS, 3);
  ZYXOR = readbit(LIS2HH12_STATUS, 7);
  if (ZYXDA == 1) {
    if (ZYXOR == 1) {
      result = 1;
    }
    readAccel(&x0, &y0, &z0);
    *x = x0 / 1000.00;
    *y = y0 / 1000.00;
    *z = z0 / 1000.00;
  }
  return (result);
}

void LIS2HH12::getAccelDataReady(float* x, float* y, float* z) {
  float x0, y0, z0;
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
    *x = x0 / 1000.00;
    *y = y0 / 1000.00;
    *z = z0 / 1000.00;
  }
}

void LIS2HH12::getAccelBDU(float* x, float* y, float* z) {
  float x0, y0, z0;
  writeRegister(8, LIS2HH12_CTRL1, 247);
  readAccel(&x0, &y0, &z0);
  *x = x0 / 1000.00;
  *y = y0 / 1000.00;
  *z = z0 / 1000.00;
}

void LIS2HH12::getAccelRAW(int* x, int* y, int* z) {
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

void LIS2HH12::setIntHPFData(uint8_t IntHPF) {
  uint8_t array[4] = {0, 1, 2, 3};
  if (!exists(array, IntHPF, 4)) {
    Serial.println("Wrong INT HPF value");
    return;
  }
  writeRegister(IntHPF, LIS2HH12_CTRL2, 252);
}

void LIS2HH12::setHPF(uint8_t HPF) {
  uint8_t array[2] = {0, 8};
  if (!exists(array, HPF, 2)) {
    Serial.println("Wrong HPF mode value");
    return;
  }
  writeRegister(HPF, LIS2HH12_CTRL2, 231);
}

void LIS2HH12::setCutOffHPF(uint8_t HPFcutOff) {
  uint8_t array[4] = {0, 32, 64, 96};
  if (!exists(array, HPFcutOff, 4)) {
    Serial.println("Wrong cut off frequency value");
    return;
  }
  writeRegister(HPFcutOff, LIS2HH12_CTRL2, 159);
}

void LIS2HH12::setReference(uint16_t x, uint16_t y, uint16_t z) {
  writeReference(x, y, z);
}

void LIS2HH12::setReferencemG(float x, float y, float z) {
  uint16_t xc, yc, zc;
  xc = referenceConvert(x);
  yc = referenceConvert(y);
  zc = referenceConvert(z);
  writeReference(xc, yc, zc);
}
//*****Interrupt Generation*****

void LIS2HH12::setIntGenerator1(char INT_1, char INT_2) {
  if (INT_1 == DISABLED_INT1) {
    writeRegister(0, LIS2HH12_CTRL3, 247);
  }
  if (INT_1 == ENABLE_INT1) {
    writeRegister(8, LIS2HH12_CTRL3, 247);
  }
  if (INT_2 == DISABLED_INT2) {
    writeRegister(0, LIS2HH12_CTRL6, 247);
  }
  if (INT_2 == ENABLE_INT2) {
    writeRegister(8, LIS2HH12_CTRL6, 247);
  }
}

void LIS2HH12::setIntGenerator2(char INT_1, char INT_2) {
  if (INT_1 == DISABLED_INT1) {
    writeRegister(0, LIS2HH12_CTRL3, 239);
  }
  if (INT_1 == ENABLE_INT1) {
    writeRegister(16, LIS2HH12_CTRL3, 239);
  }
  if (INT_1 == DISABLED_INT2) {
    writeRegister(0, LIS2HH12_CTRL6, 239);
  }
  if (INT_2 == ENABLE_INT2) {
    writeRegister(16, LIS2HH12_CTRL6, 239);
  }
}

//*****Inertial Interrupt*****

void LIS2HH12::setIntMode(uint8_t IntMode, char IG) {
  uint8_t array[4] = {0, 64, 128, 192};
  if (!exists(array, IntMode, 4)) {
    Serial.println("Wrong INT mode value");
    return;
  }
  if (IG == IG1) {
    writeRegister(IntMode, LIS2HH12_IG_CFG1, 63);
  }
  if (IG == IG2) {
    writeRegister(IntMode, LIS2HH12_IG_CFG2, 63);
  }
}

void LIS2HH12::setXYZIE(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG1, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(63, LIS2HH12_IG_CFG1, 192);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG2, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(63, LIS2HH12_IG_CFG2, 192);
    }
  }
}

void LIS2HH12::setXYZHIE(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG1, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(42, LIS2HH12_IG_CFG1, 192);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG2, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(42, LIS2HH12_IG_CFG2, 192);
    }
  }
}

void LIS2HH12::setXYZLIE(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG1, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(21, LIS2HH12_IG_CFG1, 192);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_CFG2, 192);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(21, LIS2HH12_IG_CFG2, 192);
    }
  }
}

void LIS2HH12::setXIE(uint8_t XIE, char IG) {
  uint8_t array[4] = {0, 1, 2, 3};
  if (!exists(array, XIE, 4)) {
    Serial.println("Wrong XIE value");
    return;
  }
  if (IG == IG1) {
    writeRegister(XIE, LIS2HH12_IG_CFG1, 252);
  }
  if (IG == IG2) {
    writeRegister(XIE, LIS2HH12_IG_CFG2, 252);
  }
}

void LIS2HH12::setYIE(uint8_t YIE, char IG) {
  uint8_t array[4] = {0, 4, 8, 12};
  if (!exists(array, YIE, 4)) {
    Serial.println("Wrong YIE value");
    return;
  }
  if (IG == IG1) {
    writeRegister(YIE, LIS2HH12_IG_CFG1, 243);
  }
  if (IG == IG2) {
    writeRegister(YIE, LIS2HH12_IG_CFG2, 243);
  }
}

void LIS2HH12::setZIE(uint8_t ZIE, char IG) {
  uint8_t array[4] = {0, 16, 32, 48};
  if (!exists(array, ZIE, 4)) {
    Serial.println("Wrong ZIE value");
    return;
  }
  if (IG == IG1) {
    writeRegister(ZIE, LIS2HH12_IG_CFG1, 207);
  }
  if (IG == IG2) {
    writeRegister(ZIE, LIS2HH12_IG_CFG2, 207);
  }
}

uint8_t LIS2HH12::getINT(char IG) {
  uint8_t INTG = 0;
  if (IG == IG1) {
    INTG = readbit(LIS2HH12_IG_SRC1, 6);
  }
  if (IG == IG2) {
    INTG = readbit(LIS2HH12_IG_SRC2, 6);
  }
  return (INTG);
}

void LIS2HH12::getAxisHInt(uint8_t* xh, uint8_t* yh, uint8_t* zh, char IG) {
  if (IG == IG1) {
    *xh = readbit(LIS2HH12_IG_SRC1, 1);
    *yh = readbit(LIS2HH12_IG_SRC1, 3);
    *zh = readbit(LIS2HH12_IG_SRC1, 5);
  }
  if (IG == IG2) {
    *xh = readbit(LIS2HH12_IG_SRC2, 1);
    *yh = readbit(LIS2HH12_IG_SRC2, 3);
    *zh = readbit(LIS2HH12_IG_SRC2, 5);
  }
}

void LIS2HH12::getAxisLInt(uint8_t* xl, uint8_t* yl, uint8_t* zl, char IG) {
  if (IG == IG1) {
    *xl = readbit(LIS2HH12_IG_SRC1, 0);
    *yl = readbit(LIS2HH12_IG_SRC1, 2);
    *zl = readbit(LIS2HH12_IG_SRC1, 4);
  }
  if (IG == IG2) {
    *xl = readbit(LIS2HH12_IG_SRC2, 0);
    *yl = readbit(LIS2HH12_IG_SRC2, 2);
    *zl = readbit(LIS2HH12_IG_SRC2, 4);
  }
}

void LIS2HH12::setMinDurationIG(uint8_t Duration, char IG) {
  if (Duration >= 128) {
    Serial.println("Duration value is bigger than 127");
  }
  if (IG == IG1) {
    writeRegister(Duration, LIS2HH12_IG_DUR1, 128);
  }
  if (IG == IG2) {
    writeRegister(Duration, LIS2HH12_IG_DUR2, 128);
  }
}

void LIS2HH12::setDecrementIG(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 239);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(16, LIS2HH12_CTRL7, 239);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 239);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(32, LIS2HH12_CTRL7, 223);
    }
  }
}

void LIS2HH12::setWaitIG(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_DUR1, 127);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(128, LIS2HH12_IG_DUR1, 127);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_IG_DUR2, 127);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(128, LIS2HH12_IG_DUR2, 127);
    }
  }
}

void LIS2HH12::setThresholdIG1(uint8_t X, uint8_t Y, uint8_t Z) {
  writeRegister(X, LIS2HH12_IG_THS_X1, 0);
  writeRegister(Y, LIS2HH12_IG_THS_Y1, 0);
  writeRegister(Z, LIS2HH12_IG_THS_Z1, 0);
}

void LIS2HH12::setThresholdIG2(uint8_t Threshold) {
  writeRegister(Threshold, LIS2HH12_IG_THS2, 0);
}

void LIS2HH12::setLatchedIG(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 251);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(4, LIS2HH12_CTRL7, 251);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 247);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(8, LIS2HH12_CTRL7, 247);
    }
  }
}

void LIS2HH12::setPP_OD(char PP_OD) {
  if (PP_OD == PP) {
    writeRegister(0, LIS2HH12_CTRL5, 254);
  }
  if (PP_OD == OD) {
    writeRegister(1, LIS2HH12_CTRL5, 254);
  }
}

void LIS2HH12::set4Dmode(char Status, char IG) {
  if (IG == IG1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 254);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(1, LIS2HH12_CTRL7, 254);
    }
  }
  if (IG == IG2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL7, 253);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(2, LIS2HH12_CTRL7, 253);
    }
  }
}

//************FIFO************

void LIS2HH12::setEnableFIFO(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL3, 127);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(128, LIS2HH12_CTRL3, 127);
  }
}

void LIS2HH12::setEnableFIFOThreshold(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL3, 191);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(64, LIS2HH12_CTRL3, 191);
  }
}

void LIS2HH12::setFIFO_Mode(uint8_t FIFO) {
  uint8_t array[5] = {0, 32, 64, 96, 224};
  if (!exists(array, FIFO, 5)) {
    Serial.println("Wrong FIFO mode value");
    return;
  }
  writeRegister(FIFO, LIS2HH12_FIFO_CTRL, 31);
}

void LIS2HH12::setFIFO_Threshold(uint8_t Threshold) {
  uint8_t Threshold1;
  if (Threshold >= 33) {
    Serial.println("The fifo threshold limit is 32");
    return;
  }
  Threshold1 = Threshold - 1;
  writeRegister(Threshold1, LIS2HH12_FIFO_CTRL, 224);
}

uint8_t LIS2HH12::getFTH() {
  uint8_t FTH;
  FTH = readbit(LIS2HH12_FIFO_SRC, 7);
  return (FTH);
}

uint8_t LIS2HH12::getOVR() {
  uint8_t OVR;
  OVR = readbit(LIS2HH12_FIFO_SRC, 6);
  return (OVR);
}

uint8_t LIS2HH12::getEMPTY() {
  uint8_t EMPTY;
  EMPTY = readbit(LIS2HH12_FIFO_SRC, 5);
  return (EMPTY);
}

uint8_t LIS2HH12::getFSS() {
  uint8_t read, FSS;
  read = readRegister(LIS2HH12_FIFO_SRC);
  FSS = read & 31;
  FSS += 1;
  return (FSS);
}

void LIS2HH12::setINT2Empty(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL6, 251);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(4, LIS2HH12_CTRL6, 251);
  }
}

void LIS2HH12::setINT1Ovr(char Status) {
  if (Status == LIS_DISABLED) {
    writeRegister(0, LIS2HH12_CTRL3, 251);
  }
  if (Status == LIS_ENABLE) {
    writeRegister(4, LIS2HH12_CTRL3, 251);
  }
}

void LIS2HH12::setIntFTH(char Status, char INT) {
  if (INT == INT1) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL3, 253);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(2, LIS2HH12_CTRL3, 253);
    }
  }
  if (INT == INT2) {
    if (Status == LIS_DISABLED) {
      writeRegister(0, LIS2HH12_CTRL6, 253);
    }
    if (Status == LIS_ENABLE) {
      writeRegister(2, LIS2HH12_CTRL6, 253);
    }
  }
}

//**********Status**********

uint8_t LIS2HH12::getZYXOR() {
  uint8_t ZYXOR;
  ZYXOR = readbit(LIS2HH12_STATUS, 7);
  return (ZYXOR);
}

uint8_t LIS2HH12::getZOR() {
  uint8_t ZOR;
  ZOR = readbit(LIS2HH12_STATUS, 6);
  return (ZOR);
}

uint8_t LIS2HH12::getYOR() {
  uint8_t YOR;
  YOR = readbit(LIS2HH12_STATUS, 5);
  return (YOR);
}

uint8_t LIS2HH12::getXOR() {
  uint8_t XOR;
  XOR = readbit(LIS2HH12_STATUS, 4);
  return (XOR);
}

uint8_t LIS2HH12::getZYXDA() {
  uint8_t ZYXDA;
  ZYXDA = readbit(LIS2HH12_STATUS, 3);
  return (ZYXDA);
}

uint8_t LIS2HH12::getZDA() {
  uint8_t ZDA;
  ZDA = readbit(LIS2HH12_STATUS, 2);
  return (ZDA);
}

uint8_t LIS2HH12::getYDA() {
  uint8_t YDA;
  YDA = readbit(LIS2HH12_STATUS, 1);
  return (YDA);
}

uint8_t LIS2HH12::getXDA() {
  uint8_t XDA;
  XDA = readbit(LIS2HH12_STATUS, 0);
  return (XDA);
}

//***********Temp**********

float LIS2HH12::getTemp() {
  uint8_t TEMP_L, TEMP_H;
  uint16_t TEMP;
  float TEMPC;
  TEMP_L = readRegister(LIS2HH12_TEMP_L);
  TEMP_H = readRegister(LIS2HH12_TEMP_H);
  TEMP_H = TEMP_H << 8;
  TEMP = TEMP_H | TEMP_L;
  TEMPC = TEMP * 0.125;
  return (TEMPC);
}

//*************************UTILITY*************************//

uint8_t LIS2HH12::readRegister(uint8_t regis) {
  uint8_t result = 0;
  uint8_t bytes = 1;
  Wire.beginTransmission(I2CAddress);
  Wire.write(regis);
  Wire.endTransmission();
  Wire.requestFrom(I2CAddress, bytes);
  while (Wire.available()) {
    result = Wire.read();
  }
  return result;
}

void LIS2HH12::writeRegister(uint8_t val, uint8_t regis, uint8_t bt) {
  // bt is an invert binary variable, with it you choose the bits
  // that you want read and change to zero
  uint8_t read, result, val2;
  read = readRegister(regis);
  result = read & bt;
  val2 = result | val;
  Wire.beginTransmission(I2CAddress);
  Wire.write(regis);
  Wire.write(val2);
  Wire.endTransmission();
}

void LIS2HH12::readAccel(float* x0, float* y0, float* z0) {
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

float LIS2HH12::convert(int g, int axis) {
  float axis1 = 0;
  if (axis <= 32767) {
    if (g == 2) {
      axis1 = axis * 0.061;
    }
    if (g == 4) {
      axis1 = axis * 0.122;
    }
    if (g == 8) {
      axis1 = axis * 0.244;
    }
  } else {
    float axis0;
    if (g == 2) {
      axis0 = (axis * 0.061) - 1998.8175;
      axis1 = axis0 - 1998.8175;
    }
    if (g == 4) {
      axis0 = (axis * 0.122) - 3997.635;
      axis1 = axis0 - 3997.635;
    }
    if (g == 8) {
      axis0 = (axis * 0.244) - 7995.27;
      axis1 = axis0 - 7995.27;
    }
  }
  return axis1;
}

char LIS2HH12::readbit(uint8_t regis, int loc) {
  uint8_t val;
  char bit;
  val = readRegister(regis);
  val = val >> loc;
  bit = val & 1;
  return bit;
}

char LIS2HH12::exists(uint8_t* array, uint8_t value, int size) {
  for (auto i = 0; i <= size; i++) {
    if (array[i] == value) {
      return 1;
    }
  }
  return 0;
}

uint16_t LIS2HH12::referenceConvert(float axis) {
  char FS1, FS0;
  uint16_t axis1 = 0;
  float axis0;
  FS1 = readbit(LIS2HH12_CTRL4, 5);
  FS0 = readbit(LIS2HH12_CTRL4, 4);
  if (FS1 == 0 && FS0 == 0) {
    if (axis >= 0) {
      axis1 = axis / 0.061;
    } else {
      axis0 = axis + 1998.8175;
      axis1 = (axis0 + 1998.8175) / 0.061;
    }
  }
  if (FS1 == 1 && FS0 == 0) {
    if (axis >= 0) {
      axis1 = axis / 0.122;

    } else {
      axis0 = axis + 3997.635;
      axis1 = (axis0 + 3997.635) / 0.122;
    }
  }
  if (FS1 == 1 && FS0 == 1) {
    if (axis >= 0) {
      axis1 = axis / 0.244;
    } else {
      axis0 = axis + 7995.27;
      axis1 = (axis0 + 7995.27) / 0.244;
    }
  }
  return (axis1);
}
void LIS2HH12::writeReference(uint16_t x, uint16_t y, uint16_t z) {
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