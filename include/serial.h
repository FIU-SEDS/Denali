#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

// Add all the sensors here, suffixed with _ID. This is how we indicate what
// bytes mean in sequence when doing any kind of IO (files, radio, in our case).

typedef enum : uint8_t {
  BME_ID, 
  IMU_ID, 
  GPS_ID
} sensor_ID;

#endif // SERIAL_H
