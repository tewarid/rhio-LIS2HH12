#include <Arduino.h>
#define S100_ESP32_WROOM_32_v1_0
#include <rhio-LIS2HH12.h>
#include <rhio-pinmap.h>

float temp;
LIS2HH12 lis = LIS2HH12();
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Temp LIS2HH12 example");
  lis.begin();
  lis.setFrequency(16);
  lis.setHPF(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = lis.getTemp();
  Serial.print("T: ");
  Serial.println(temp);
  delay(2000);
}
