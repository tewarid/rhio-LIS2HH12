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

#include "rhio-LIS2HH12 - Training.h"

/***************************************************************************
 *                          Constructor
 **************************************************************************/

// Al constructor se le pasa la dirección I2C
LIS2HH12::LIS2HH12() { I2CAddress = 0x1D; }

/***************************************************************************
 *                          Initialization
 **************************************************************************/

// Inicialización del sensor
void LIS2HH12::begin() {
  Wire.begin();    // Inicializa I2C
  setSoftReset();  // Se hace un reset del sensor, para que no haya nada escrito
                   // en los registros
}

/***************************************************************************
 *                          Basic function
 **************************************************************************/

// Función para configurar lo mas básico del sensor
void LIS2HH12::setBasicConfig() { writeRegister(23, LIS2HH12_CTRL1, 0); }

/***************************************************************************
 *                          Operating Modes
 **************************************************************************/

// Ajuste de la frecuencia de medidada mediante el parametro ODR
void LIS2HH12::setFrequency(uint8_t ODR) {
  writeRegister(ODR, LIS2HH12_CTRL1, 143);
}

// Ajuste de los ejes que se usan mediante el parametro ZYX
void LIS2HH12::setAxis(uint8_t ZYX) { writeRegister(ZYX, LIS2HH12_CTRL1, 248); }

// Ajuste del fondo escala que se usa mediante el parametro FS
// Este sensor tiene tres fondos escala (+/-) 2, 4, 8
void LIS2HH12::setFS(uint8_t FS) { writeRegister(FS, LIS2HH12_CTRL4, 207); }

// Reset del sensor
void LIS2HH12::setSoftReset() { writeRegister(64, LIS2HH12_CTRL5, 191); }

/***************************************************************************
 *                   Reading Accerlation Data Modes
 **************************************************************************/

// Lectura de la aceleración, para ello se usan tres punteros x, y, z que
// apuntan a x0, y0 y z0.
// La salia de la acelración es en mg, para pasarlo a g, se divide entre 1000.
void LIS2HH12::getAccel(float* x, float* y, float* z) {
  float x0, y0, z0;
  readAccel(&x0, &y0, &z0);
  *x = x0 / 1000.00;
  *y = y0 / 1000.00;
  *z = z0 / 1000.00;
}

/***************************************************************************
 *                              UTILITY
 **************************************************************************/

// Lectura de los registros mediante el protocolo de comunicación I2C
// A la función se le pasa el registro que se desea leer
uint8_t LIS2HH12::readRegister(uint8_t regis) {
  uint8_t result = 0;
  uint8_t bytes = 1;
  Wire.beginTransmission(
      I2CAddress);         // Se pasa la dirección de I2C en su inicialización
  Wire.write(regis);       // Se manda el registro que se desea leer
  Wire.endTransmission();  // Se finaliza transmisión
  Wire.requestFrom(I2CAddress, bytes);  // Se pide información volviendo a
                                        // mandar la dirección y el registro
  while (Wire.available()) {
    result = Wire.read();  // Mientras el canal este abierto, guarda los datos
                           // en la variable result
  }
  return result;
}

// Escritura de los registros mediante el protocolo de comunicación I2C
void LIS2HH12::writeRegister(uint8_t val, uint8_t regis, uint8_t bt) {
  // La función de escritura tiene tres parametros de entrada, val (valor que se
  // quiere escribir), regis(registro donde se va a escribir el valor) y bt
  // (palabra del tamaño del registro para poner a 0 los bits que se desean
  // configurar y el resto dejarlos igual)
  uint8_t read, result, val2;
  read = readRegister(regis);  // Lectura del registro
  result = read & bt;  // Se multiplica por bt para poner a 0 los valores que se
                       // quieren configurar
  val2 = result | val;  // El resultado anterior se le suma a la palabra val
  Wire.beginTransmission(I2CAddress);
  Wire.write(regis);
  Wire.write(val2);
  Wire.endTransmission();
}

// Función de lectura original
// Cada eje tiene dos registros, uno para los de menos significativos (XL, YL,
// ZL) y otra para los mas significativos (XH, YH, ZH).
void LIS2HH12::readAccel(float* x0, float* y0, float* z0) {
  uint8_t XL, XH, YL, YH, ZH, ZL;
  int x01, y01, z01;
  char FS1, FS0;  // Variables para leer que fondo escala esta configurado
  // Lectura de los registros necesarios
  XL = readRegister(LIS2HH12_OUT_X_L);
  XH = readRegister(LIS2HH12_OUT_X_H);
  YL = readRegister(LIS2HH12_OUT_Y_L);
  YH = readRegister(LIS2HH12_OUT_Y_H);
  ZL = readRegister(LIS2HH12_OUT_Z_L);
  ZH = readRegister(LIS2HH12_OUT_Z_H);
  FS1 = readbit(LIS2HH12_CTRL4, 5);
  FS0 = readbit(LIS2HH12_CTRL4, 4);
  // Como los registros son de 8 bits, la lectura de la parte más significativa
  // de los ejes se mueve 8 posiciones a la izquierda y se le suma la parte
  // menos significativa.
  x01 = XH << 8 | XL;
  y01 = YH << 8 | YL;
  z01 = ZH << 8 | ZL;
  // A la función convert se le pasa el fondo escala y el valor de medida (x01,
  // y01, z01)
  // Fondo escala de +/- 2g
  if (FS1 == 0 && FS0 == 0) {
    *x0 = convert(2, x01);
    *y0 = convert(2, y01);
    *z0 = convert(2, z01);
  }
  // Fondo escala de +/- 4g
  if (FS1 == 1 && FS0 == 0) {
    *x0 = convert(4, x01);
    *y0 = convert(4, y01);
    *z0 = convert(4, z01);
  }
  // Fondo escala de +/- 8g
  if (FS1 == 1 && FS0 == 1) {
    *x0 = convert(8, x01);
    *y0 = convert(8, y01);
    *z0 = convert(8, z01);
  }
}

// Conversion usando la sensibilidad proporcionada por la hoja de datos.
float LIS2HH12::convert(int g, int axis) {
  float axis1 = 0;
  // De 0 a 32767 la aceleracón es positiva. A partir de este valor,
  // es negativa. La parte negativa es de mas a menos negativa.
  if (axis <= 32767) {
    if (g == 2) {
      // La sensibilidad es de 0.061 para el fondo escala de +/- 2 g
      axis1 = axis * 0.061;
    }
    if (g == 4) {
      // La sensibilidad es de 0.122 para el fondo escala de +/- 4 g
      axis1 = axis * 0.122;
    }
    if (g == 8) {
      // La sensibilidad es de 0.244 para el fondo escala de +/- 8 g
      axis1 = axis * 0.244;
    }
  } else {
    float axis0;
    if (g == 2) {
      // Al valor calculado se le resta el maximo valor que es capaz de medir
      axis0 = (axis * 0.061) - 1998.8175;
      // Como el mayor numero no es el más negativo, se tiene que volver a
      // restar el maximo valor que es capaz de medir
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

// Lectura de un bit determinado
char LIS2HH12::readbit(uint8_t regis, int loc) {
  uint8_t val;
  char bit;
  val = readRegister(regis);
  // El valor de lectura se desplaza hasta la posición del bit deseado.
  val = val >> loc;
  // Para obtener solo el bit, se multiplica el valor desplazado por 1.
  bit = val & 1;
  return bit;
}
