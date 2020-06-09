#include <Arduino.h>
#include <rhio-LIS2HH12.h>

LIS2HH12 lis = LIS2HH12();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  lis.begin();
  Serial.println("6D position detection LIS2HH12 example");
  lis.setFrequency(48);  // 100 Hz
  lis.setAxis(7);        // XYZ
  lis.setFS(0);          // 2g
  lis.setXYZIE(1, IG1);
  lis.setIntMode(192, IG1);
  lis.setThresholdIG1(10, 10, 10);
  // If yo do bigger this value, you have a worse resolution
  // But it will be easier position detection
}

void loop() {
  // put your main code here, to run repeatedly:
  // It's important to read the LIS2HH12 aplicattions notes to undersantd the
  // position
  uint8_t x1, y1, z1, x2, y2, z2;
  lis.getAxisHInt(&x1, &y1, &z1, IG1);
  lis.getAxisLInt(&x2, &y2, &z2, IG1);
  Serial.print("xH: ");
  Serial.println(x1);
  Serial.print("yH: ");
  Serial.println(y1);
  Serial.print("zH: ");
  Serial.println(z1);
  Serial.print("xL: ");
  Serial.println(x2);
  Serial.print("yL: ");
  Serial.println(y2);
  Serial.print("zL: ");
  Serial.println(z2);
  delay(2000);
}