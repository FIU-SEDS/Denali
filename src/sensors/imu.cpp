#include <BMI088.h>
#include <SPI.h>

#include <sensors.h>

bmi088Accel accel(SPI,  CS_BMI088_ACCL);
bmi088Gyro  gyro (SPI,   CS_BMI088_GYRO);

bool BMI_begin() {

  int status = accel.begin();
  if(status < 0)
    return true;

  status = gyro.begin();
  if(status < 0)
    return true;

  return false;
}


