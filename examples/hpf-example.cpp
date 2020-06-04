#include <Arduino.h>
#include <rhio-LIS2HH12.h>

float x, y, z, x1, y2, z1;

LIS2HH12 lis = LIS2HH12();
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("HPF LIS2HH12 example");
  lis.begin();
  lis.setAxis(7);
  lis.setFrequency(16);
  lis.setFS(0);
  lis.setActiveInactive(0, 0);
  lis.setReference(400, 0, 0);
  lis.setHPF(8);
  lis.setFDS(ONDHPF);
}

void loop() {
  // put your main code here, to run repeatedly:
  char t = lis.getAccelmG(&x, &y, &z);
  x1 = x;
  y2 = y;
  z1 = z;

  Serial.print("x: ");
  Serial.println(x1);
  Serial.print("y: ");
  Serial.println(y2);
  Serial.print("z: ");
  Serial.println(z1);
  Serial.println(t);
  delay(2000);
}
