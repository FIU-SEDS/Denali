#ifndef SENSORS_H
#define SENSORS_H

#define CS_BMI088_GYRO 0
#define CS_BMI088_ACCL

// TEMPORARY CHIP SELECT DEFINES HERE FOR GIT CONVENIENCE. CHANGE LATER

struct IMU_data {
  float acl_x, acl_y, acl_z;
  float gyro_x, gyro_y, gyro_z;
};

struct THM_data {
  float temp, humid;
  float axis_x, axis_y, axis_z;
};

struct GPS_data {
  int x, y;
};

#endif // SENSORS_H
