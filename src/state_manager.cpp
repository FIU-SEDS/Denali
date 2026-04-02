#include <state_manager.h>
#include <sensors.h>
#include <vector>
#include <cstdint>
#include <io.h>
#include <sensors.h>
#define ARRLEN(_x) ((sizeof(_x)) / (sizeof(_x[0])))


// Rocket State parameter thresholds
constexpr uint8_t G_FORCE_THRESHOLD = 3;                                                       // unit 1 G
constexpr float GRAVITY_TO_METERS_PER_SECOND = 9.80665;                                        // measured in m/s^2
constexpr float LINEAR_ACCEL_Z_THRESHOLD = (G_FORCE_THRESHOLD * GRAVITY_TO_METERS_PER_SECOND); // set to 3Gs; change the G_FORCE_THRESHOLD to set what amount of Gs the rocket will measure until it switches to BOOST
constexpr uint16_t ALTITUDE_THRESHOLD = 50;  // unit FEET

// first rocket state
enum rocket_state state = IDLE;
//rocket_state rocket = IDLE;                                                                    // tentative placement to not get any errors

constexpr uint8_t COAST_ITERARTIONS = 100;                                                     // this variables holds the amount of times that we will check that the rocket is sitll not accelerating to ensure that the rocket is in COAST stage
constexpr uint8_t APOGEE_ITERATIONS = 10;                                                      // this variable holds the amount of times we will check that the rockets previous altitude is greater than its current one to determine that the rocket has indeed reached APOGEE stage
constexpr uint16_t MAIN_PARACHUTE_THRESHOLD = 1000;                                            // unit FEET where main parachute is set to deploy

double previous_altitude = 0;    // this variable is set to keep track of a previous baseline altitude to refer to
uint8_t coast_sample_count = 0;  // used to verify that the coast counter reaches 100 to switch states
uint8_t apogee_sample_count = 0; // used to verify that the current altitude measurement in COAST stage is lower than the previous reading and repeated 5 times to ensure that the rocket is in apogee

void log_state_change();

//===============================================
//*CHANGE THE GLOBAL SENSOR VALUE ARRAY TO THE ACTUAL SENSOR VALUES PROCESSED*
//===============================================


rocket_state update_rocket_states(rocket_state state, GPS_data &gps_data, BME_data &bme_data, IMU_data &imu_data, MAG_data &mag_data)
{
    switch (state)
    {
    //start with IDLE on the state machine since the rocket will be in that state after initialization and then it will switch to BOOST once the rocket experiences 3 Gs or reaches 50 feet in altitude.
    case IDLE:
  
        if (imu_data.acl_z > LINEAR_ACCEL_Z_THRESHOLD || bme_data.altitude > ALTITUDE_THRESHOLD)
        {
        return BOOST;
        }
     break;

    case BOOST:
        if (imu_data.acl_z < LINEAR_ACCEL_Z_THRESHOLD || bme_data.altitude > previous_altitude)
        {
        return BURNOUT;
        }
        break;

    case BURNOUT:
        if (imu_data.acl_z < LINEAR_ACCEL_Z_THRESHOLD)
        {
        coast_sample_count++;
        if (coast_sample_count >= COAST_ITERARTIONS)
        {
            return COAST;
            coast_sample_count = 0;
         }
        }
        else
        {
      coast_sample_count = 0; // reset counter if acceleration is still detected
        }
        break;

    case COAST:
        if (bme_data.altitude < previous_altitude)
        {
        apogee_sample_count++;
        if (apogee_sample_count >= APOGEE_ITERATIONS)
        {
            return APOGEE;
            apogee_sample_count = 0; // reset counter
        }
        }
        else
        {
        apogee_sample_count = 0; // reset if altitude is still increasing
        }
        break;

    case APOGEE:
        // write a function here to timestamp "Drogue parachute deployment"
        return DESCENT_DROGUE;
        break;

    case DESCENT_DROGUE:
        if (bme_data.altitude < MAIN_PARACHUTE_THRESHOLD)
        {
        return DESCENT_MAIN;
        }
        break;

    case DESCENT_MAIN:
        if (imu_data.acl_z < LINEAR_ACCEL_Z_THRESHOLD || bme_data.altitude < ALTITUDE_THRESHOLD)
        {
        return LANDED;
        }
        break;

    case LANDED:
    // write a function here to timestamp "Rocket has landed"
        break;
    default:
        break;
    }
    previous_altitude = bme_data.altitude; // updates previous altitude for the next iteration
    return state; // if no state change occurs, return the current state
    }




void log_state_change()
{
  char b_arr[] = {ROCKET_STATE, (char) rocket};
  transmit_data(b_arr, 2);
  store_data((unsigned char*) b_arr, 2);
}

