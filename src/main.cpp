#include <SPI.h>
#include <serial.h>
#include <sensors.h>
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
  GPS_data gd;
  rocket_state state;

  if(MMC_process(md) ||
     BMI_process(id) ||
     BME_process(bd))
  {
    // an error has occured
  }

}
