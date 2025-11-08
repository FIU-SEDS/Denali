#include <Adafruit_BME280.h>
#include <stdint.h>

constexpr int8_t LOWER_TEMP_BOUND = -30; // degrees Celsius
constexpr int8_t UPPER_TEMP_BOUND = 75; // degrees Celsius
constexpr uint8_t BME_CS = PB11; // stm32
constexpr uint8_t BME_CHIP_ID = 0xD0;

Adafruit_BME280 bme(BME_CS); // hardware SPI init
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI init
// Adafruit_BME280 bme

bool is_device_connected() {
   digitalWrite(BME_CS, LOW);
    
    SPI.transfer(BME_CHIP_ID | 0x80);  // Tell BME280: "I want to READ register 0xD0" and use 0x80(128) because for read operations, bit 7 of the register address must be set to 1
    uint8_t chip_id = SPI.transfer(0x00);  // Read the value (should be 0x60)
    
    digitalWrite(BME_CS, HIGH);
    
    return (chip_id == 0x60);  // True if BME280 detected
}

bool init_bme() {
    // TODO not using Serial.print write a function call to produce error for all 3 checks

  if (!bme.begin()) {
    return false;
  }

  if(!is_device_connected()) {
    return false;
  }

  float temp = bme.readTemperature(); // read temp to verify
  if (temp < LOWER_TEMP_BOUND || temp > UPPER_TEMP_BOUND) {
    return false;
  }

  return true;
}