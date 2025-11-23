#include <Adafruit_BME280.h>
#include <sensors.h>
#include <stdint.h>

constexpr int8_t LOWER_TEMP_BOUND = -30; // degrees Celsius
constexpr int8_t UPPER_TEMP_BOUND = 75; // degrees Celsius
constexpr float PRESSURE_LOWER_BOUND = 300.0F; // in hPa
constexpr float PRESSURE_UPPER_BOUND = 1100.0F; // in hPa
constexpr uint8_t BME_CS = PB11; // stm32
constexpr uint8_t BME_CHIP_ID = 0x60;
constexpr float SEA_LEVEL_PRESSURE_HPA = 1013.25; // standard atmosphere
constexpr float METERS_TO_FEET = 3.280839895;
constexpr float MAX_EXPECTED_ALTITUDE_FT = 35000.0F;  // ~10 km
constexpr float MIN_EXPECTED_ALTITUDE_FT = -500.0F;   // Allow some below ground level

Adafruit_BME280 bme(BME_CS); // hardware SPI init
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI init
// Adafruit_BME280 bme

// CHeck if BME is responding
bool is_device_connected() {
  return (bme.sensorID() == BME_CHIP_ID);
}

bool init_bme() {

  if (!bme.begin()) return false;
  if (!is_device_connected()) return false;

  float temp = bme.readTemperature();
  if (isnan(temp) || temp < LOWER_TEMP_BOUND || temp > UPPER_TEMP_BOUND) return false;

  // bme configuration PLACE HERE
  bme.setSampling(
        Adafruit_BME280::MODE_NORMAL,      // Continuous readings
        Adafruit_BME280::SAMPLING_X16,     // Temperature oversampling
        Adafruit_BME280::SAMPLING_X16,     // Pressure oversampling  
        Adafruit_BME280::SAMPLING_X16,     // Humidity oversampling
        Adafruit_BME280::FILTER_X16,       // IIR filter
        Adafruit_BME280::STANDBY_MS_0_5    // 0.5ms standby
  );
    
  return true;
}

bool process_bme(BME_data &baro) {
  baro.temp = bme.readTemperature(); // celcius
  baro.humidity = bme.readHumidity(); // percentage
  baro.pressure = bme.readPressure() / 100.0F; // from Pa to hPa 
  baro.altitude = bme.readAltitude(SEA_LEVEL_PRESSURE_HPA) * METERS_TO_FEET; // in feet


  // validating readings
  if (isnan(baro.temp) || isnan(baro.humidity) || isnan(baro.pressure)) return false;

 /* 
  * because 300 hPA is (30,000 feet) roughly and 1100 is practically below sea level then sensor is malfunctioning so performing a sanity check
  */
  if (baro.pressure < PRESSURE_LOWER_BOUND || baro.pressure > PRESSURE_UPPER_BOUND) return false;

  // validating rockets altitude
  if (baro.altitude < MIN_EXPECTED_ALTITUDE_FT || baro.altitude > MAX_EXPECTED_ALTITUDE_FT) return false;


  return true;
}
