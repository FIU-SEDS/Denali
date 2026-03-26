#ifndef SENSORS_H
#define SENSORS_H

#include <serial.h>

#define CS_BMI088_GYRO 0
#define CS_BMI088_ACCL 0 

// TEMPORARY CHIP SELECT DEFINES HERE FOR GIT CONVENIENCE. CHANGE LATER

struct IMU_data {
  const sensor_ID ID = IMU_ID;
  float acl_x, acl_y, acl_z;
  float gyro_x, gyro_y, gyro_z;
};

struct BME_data {
  const sensor_ID ID = BME_ID;
  float temp, humidity, pressure, altitude;
};

struct MAG_data {
  const sensor_ID ID = MAG_ID;
  float heading;
};

//I added altitude to the struct for GPS data.
struct GPS_data {
  const sensor_ID ID = GPS_ID;
  float latitude, longitude, altitude;
};
// headers for GPS
bool GNSS_begin();
bool GNSS_process(GPS_data &gnss_data);

bool MMC_begin();
bool MMC_process(MAG_data &mag_data);

bool BMI_begin();
bool BMI_process(IMU_data &data);

bool BME_begin();
bool BME_process(BME_data &baro);


#endif // SENSORS_H
