#include <SPI.h>
#include <serial.h>
#include "sensors.h"
#include <state_manager.h>

void setup() {
  Serial.begin(115200);

  if(MMC_begin() ||
     BMI_begin() ||
     BME_begin()) {
    // do something LOL
  }
  
  SPI.begin(); // init the SPI bus
}

void loop() {

  MAG_data md;
  IMU_data id;
  BME_data bd;

  if(MMC_process(md) ||
     BMI_process(id) ||
     BME_process(bd))
  {
    // an error has occured
  }

  //===============================================
  // This is my logic to how the state manager will work with the current sensor functions
  // and update_rocket_states_function.

  current_sensor(); // this will update the sensor data to the most recent values
  update_rocket_states() //will determine the state of the rocket and return that state



}
