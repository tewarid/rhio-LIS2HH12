#include <Arduino.h>
#include <rhio-LIS2HH12.h>

#define Threshold 4

LIS2HH12 lis = LIS2HH12();
float x, y, z;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  lis.begin();
  Serial.println("FIFO LIS2HH12 example");
  lis.setFrequency(48);  // 100 Hz
  lis.setAxis(7);        // XYZ
  lis.setFS(0);          // 2g
  lis.setFIFO_Threshold(Threshold);
  lis.setEnableFIFOThreshold(LIS_ENABLE);
  lis.setEnableFIFO(LIS_ENABLE);
  lis.setFIFO_Mode(0);   // FIFO reset
  lis.setFIFO_Mode(32);  // FIFO mode
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t samples;
  if (lis.getFTH() == 1) {
    Serial.println("FIFO is bigger than threshold");
    for (auto i = 1; i <= Threshold; i++) {
      lis.getAccel(&x, &y, &z);
      Serial.print("x: ");
      Serial.print(x);
      Serial.print(", y: ");
      Serial.print(y);
      Serial.print(", z: ");
      Serial.println(z);
    }
    lis.setFIFO_Mode(0);
    lis.setFIFO_Mode(32);
  }
  samples = lis.getFSS();
  Serial.print("Value's number without read: ");
  Serial.println(samples);
}