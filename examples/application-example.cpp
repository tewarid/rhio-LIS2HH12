#include <Arduino.h>
#include <rhio-LIS2HH12.h>

float time1, time2, time3;
float x3, y3, z3;
char x2, y2, z2;

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
  if (lis.getIsMoving()) {
    lis.getAccel(&x3, &y3, &z3);  // g
    Serial.print("x: ");
    Serial.println(x3, 4);
    Serial.print("y: ");
    Serial.println(y3, 4);
    Serial.print("z: ");
    Serial.println(z3, 4);
    time1 = lis.getActiveTime();
    Serial.print("Active time: ");  // seg
    Serial.println(time1 / 1000, 2);
  }
  Serial.print("Active time 2: ");
  Serial.println(time2 / 1000, 2);
  time2 = lis.getActiveTime2();
}