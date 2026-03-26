#pragma once
#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include <cstdint>

enum axes : uint8_t
{
  X,
  Y,
  Z
};

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
  // for logging purposes only
  ROCKET_STATE
};

extern enum rocket_state rocket;

// State manager functions
bool initialize_all_components(); // if one sensor's power on function returns false then it will reset the teensy 4.1

rocket_state update_rocket_states(rocket_state state); // determines which state the rocket is in and returns that state=

void current_sensor(); // runs the current sensor's to update the object data to the most recent values


bool run_priority_sensor(rocket_state rs);

/**
 * @brief Checks if a device at the specified I2C address is responsive
 * @param 8-bit address The I2C address to check
 * @return true if the device responds to I2C request, false otherwise
 */
bool is_device_connected(uint8_t address);

/**
 * @brief Initializes the MMC5983MA magnetometer and performs startup checks
 * @details Initializes the sensor, performs a soft reset, verifies I2C connectivity,
 *          and checks that temperature is within operating range
 * @return true if initialization and all checks pass, false otherwise
 */
bool power_on_magnetometer();

/**
 * @brief Initializes the MS5611 barometer and performs startup checks
 * @details Initializes the sensor, verifies I2C connectivity, and checks that
 *          temperature is within operating range
 * @return true if initialization and all checks pass, false otherwise
 */
bool power_on_barometer();

/**
 * @brief Initializes the HTU21DF temperature and humidity sensor and performs startup checks
 * @details Initializes the sensor, verifies I2C connectivity, and checks that
 *          temperature is within operating range
 * @return true if initialization and all checks pass, false otherwise
 */
bool power_on_temp_and_humidity();

/**
 * @brief Initializes the ASM330LHH backup IMU and performs startup checks
 * @details Initializes the sensor, enables accelerometer and gyroscope components,
 *          and verifies I2C connectivity
 * @return true if initialization and all checks pass, false otherwise
 */
bool power_on_backup_IMU();

/**
 * @brief Initializes the BNO055 main IMU and performs startup checks
 * @details Initializes the sensor, configures it to use external crystal for better accuracy,
 *          verifies I2C connectivity, and checks that temperature is within operating range
 * @return true if initialization and all checks pass, false otherwise
 */
bool power_on_main_IMU();

/**
 * @brief Initializes the MCP7940 Real Time Clock and performs startup checks
 * @details Initilizes sensor, checks the status of the device and ensures that the oscillator is running,
 *          verifies I2C connection, and sets to current time
 * @return true if initialization and all checks pass, fail otherwise
 * */
bool power_on_real_time_clock();

//bool power_on_GPS();

// bool process_gps();
bool process_temp_and_humidity();
bool process_barometer();
bool process_IMUs();
bool process_magnetometer();
//bool process_real_time_clock();

/**
 * @brief Initializes and configures the RYLR998 LoRa Radio Module. 
 * @details Sends AT commands to set the LoRa mode, device address, frequency band(915 MHz), and baud rate. 
 *          This prepares the module for data transmission. 
 * @returns \\To be determined...
 */
bool power_on_lora_998();

bool power_on_storage();


#endif
