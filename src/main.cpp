#include <Arduino.h>
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  while (!Serial); // time to get serial running
  
  SPI.begin(); // init the SPI bus
}

void loop() {
  Serial.println("Test");
}
