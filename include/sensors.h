#ifndef SENSORS_H
#define SENSORS_H

#define CS_BMI088_GYRO 0
#define CS_BMI088_ACCL 0 
#define BME_CS 10

// TEMPORARY CHIP SELECT DEFINES HERE FOR GIT CONVENIENCE. CHANGE LATER

struct IMU_data {
  float acl_x, acl_y, acl_z;
  float gyro_x, gyro_y, gyro_z;
};

struct BME_data {
  float temp, humidity, pressure, altitude;
};

struct GPS_data {
  float latitude, longitude;
};

bool init_bme();
void test_BME(BME_data &baro);
bool process_bme(BME_data &baro);

#endif // SENSORS_H
