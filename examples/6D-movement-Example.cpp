#include <Arduino.h>
#define S100_ESP32_WROOM_32_v1_0
#include <rhio-LIS2HH12.h>
#include <rhio-pinmap.h>

LIS2HH12 lis = LIS2HH12();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  lis.begin(I2C_MODE);
  Serial.println("6D position movement LIS2HH12 example");
  lis.setFrequency(48);  // 100 Hz
  lis.setAxis(7);        // XYZ
  lis.setFS(0);          // 2g
  lis.setXYZIE(1, IG1);
  lis.setIntMode(64, IG1);
  lis.setThresholdIG1(10, 10, 10);
}

void loop() {
  // put your main code here, to run repeatedly:

  char x1, y1, z1, x2, y2, z2;
  int x11, y11, z11, x22, y22, z22;
  lis.getAxisHInt(&x1, &y1, &z1, IG1);
  lis.getAxisLInt(&x2, &y2, &z2, IG1);
  x11 = x1;
  y11 = y1;
  z11 = z1;
  x22 = x2;
  y22 = y2;
  z22 = z2;
  Serial.print("xH: ");
  Serial.println(x11);
  Serial.print("yH: ");
  Serial.println(y11);
  Serial.print("zH: ");
  Serial.println(z11);
  Serial.print("xL: ");
  Serial.println(x22);
  Serial.print("yL: ");
  Serial.println(y22);
  Serial.print("zL: ");
  Serial.println(z22);
  delay(2000);
}