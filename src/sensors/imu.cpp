#include <BMI088.h>
#include <SPI.h>

#include <sensors.h>

Bmi088Accel accel(SPI, CS_BMI088_ACCL);
Bmi088Gyro gyro(SPI, CS_BMI088_GYRO);

bool BMI_begin()
{

  int status = accel.begin();
  if (status < 0)
    return true;

  status = gyro.begin();
  if (status < 0)
    return true;

  return false;
}

bool BMI_process(IMU_data &data) {
{
  IMU_data data;

  data.acl_x = accel.getAccelX_mss();
  data.acl_y = accel.getAccelY_mss();
  data.acl_z = accel.getAccelZ_mss();

  data.gyro_x = gyro.getGyroX_rads();
  data.gyro_y = gyro.getGyroY_rads();
  data.gyro_z = gyro.getGyroZ_rads();

  return data;
}
