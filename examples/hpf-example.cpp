#include <Arduino.h>
#define S100_ESP32_WROOM_32_v1_0
#include <rhio-LIS2HH12.h>
#include <rhio-pinmap.h>

float x, y, z, x1, y2, z1;
int x3, y3, z3, x4, y4, z4;

LIS2HH12 lis = LIS2HH12();
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("HPF LIS2HH12 example");
  lis.begin(I2C_MODE);
  lis.setAxis(7);
  lis.setFrequency(16);
  lis.setFS(0);
  lis.setActiveInactive(0, 0);
  lis.setReference(65400, 65510, 65510);
  lis.setHPF(8);
  lis.setFDS(ONHPF);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool t = lis.getAccel(&x, &y, &z);
  lis.getAccelRAU(&x3, &y3, &z3);
  x1 = x;
  y2 = y;
  z1 = z;
  x4 = x3;
  y4 = y3;
  z4 = z3;

  Serial.print("x: ");
  Serial.println(x1);
  Serial.print("y: ");
  Serial.println(y2);
  Serial.print("z: ");
  Serial.println(z1);
  Serial.print("x1: ");
  Serial.println(x4);
  Serial.print("y1: ");
  Serial.println(y4);
  Serial.print("z1: ");
  Serial.println(z4);
  Serial.println(t);
  delay(2000);
}
