#include <Arduino.h>
#include <rhio-LIS2HH12.h>

LIS2HH12 lis = LIS2HH12();
float x, y, z;
uint8_t x2, y2, z2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  lis.begin();
  Serial.println("Wake-up LIS2HH12 example");
  lis.setFrequency(16);  // 10 Hz
  lis.setAxis(3);        // XY
  lis.setFS(0);          // 2g
  lis.setFDS(ONDLPF);
  lis.setPP_OD(PP);
  lis.setIntMode(0, IG2);
  lis.setXIE(2, IG2);
  lis.setYIE(8, IG2);
  lis.setThresholdIG2(40);
  lis.setMinDurationIG(10, IG2);  // 1 seg
}

void loop() {
  // put your main code here, to run repeatedly:
  if (lis.getINT(IG2) == 1) {  // Also you can read only axis INT
    Serial.println("I wake-up");
    lis.getAccel(&x, &y, &z);
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
    Serial.print("z: ");  // The Z isn't set, don't read anything
    Serial.println(z);
  }
  lis.getAxisHInt(&x2, &y2, &z2, IG2);
  Serial.print("xH: ");
  Serial.println(x2);
  Serial.print("yH: ");
  Serial.println(y2);
  delay(2000);
}