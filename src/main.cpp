#include <Arduino.h>
#define S100_ESP32_WROOM_32_v1_0
#include <rhio-pinmap.h>
#include <rhioJF-LIS2HH12.h>

int P;
LIS2HH12 lis = LIS2HH12();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Prueba libreria ARRAY");
  lis.setFrequency(80);
}

void loop() {
  // put your main code here, to run repeatedly:
}