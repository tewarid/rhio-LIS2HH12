#include <Arduino.h>
#include <rhio-LIS2HH12.h>

float x, y, z;
LIS2HH12 lis = LIS2HH12();
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("LIS2HH12 example");
  lis.begin();
  lis.setBasicConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
  lis.getAccel(&x, &y, &z);
  Serial.print("x: ");
  Serial.println(x, 3);
  Serial.print("y: ");
  Serial.println(y, 3);
  Serial.print("z: ");
  Serial.println(z, 3);
  delay(2000);
}