#pragma once
#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include <cstdint>
#include <sensors.h>


// Flight states
enum rocket_state : uint8_t
{
  INIT,
  IDLE,
  BOOST,
  BURNOUT,
  COAST,
  APOGEE,
  DESCENT_DROGUE,
  DESCENT_MAIN,
  LANDED,
};

enum sensors : uint8_t
{
  ROCKET_STATE
};


rocket_state update_rocket_states(rocket_state state, GPS_data &gps_data, BME_data &bme_data, IMU_data &imu_data, MAG_data &mag_data);




#endif
