#include <stdint.h>
#include <SPI.h>

enum sensor_readouts : uint8_t // this is to be used as the index for the global array!
{
  PRESSURE,    // barometer in pascals
  ALTITUDE,    // barometer in feet
  TEMPERATURE, // temp
  HUMIDITY,    // humid
  SENSOR_READOUTS_AMOUNT // number of sensor readouts in enum
};

// extern float global_sensor_vals[SENSORS_AMOUNT]; // defunct! We want a global array of all the sensor readouts.
extern float global_sensor_vals[SENSOR_READOUTS_AMOUNT];

bool is_device_connected(uint8_t address);