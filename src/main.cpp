#include <Arduino.h>
#define S100_ESP32_WROOM_32_v1_0
#include <rhio-LIS2HH12.h>
#include <rhio-pinmap.h>

LIS2HH12 lis = LIS2HH12();
float x, y, z;
char x2, y2, z2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  lis.begin(I2C_MODE);
  Serial.println("Free-fall LIS2HH12 example");
  lis.setFrequency(48);  // 100 Hz
  lis.setAxis(7);        // XYZ
  lis.setFS(0);          // 2g
  lis.setFDS(ONLPF);
  lis.setPP_OD(PP);
  lis.setIntMode(128, IG1);
  lis.setXIE(1, IG1);
  lis.setYIE(4, IG1);
  lis.setZIE(16, IG1);
  lis.setThresholdIG1(90, 90, 90);
  lis.setMinDurationIG(0, IG1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (lis.getINT(IG1) == 1) {  // Also you can read only axis INT
    Serial.println("Bro I free-fall");
    lis.getAccel(&x, &y, &z);
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
    Serial.print("z: ");
    Serial.println(z);
  }
  lis.getAxisLInt(&x2, &y2, &z2, IG1);
  Serial.print("xL: ");
  Serial.println(x2);
  Serial.print("yL: ");
  Serial.println(y2);
  Serial.print("zL: ");
  Serial.println(z2);
  delay(2000);
}