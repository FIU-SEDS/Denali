#ifndef SENSORS_H
#define SENSORS_H

#define CS_BMI088_GYRO 0
#define CS_BMI088_ACCL

// TEMPORARY CHIP SELECT DEFINES HERE FOR GIT CONVENIENCE. CHANGE LATER

struct IMU_data {
  float acl_x, acl_y, acl_z;
  float gyro_x, gryo_y, gyro_z;
};

struct BME_data {
  float temp, humidity, pressure, altitude;
};


struct GPS_data {
  float latitude, longitude;
};

extern BME_data bme_data;

#endif // SENSORS_H
