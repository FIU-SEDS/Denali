/*
  Compute magnetic heading over SPI from the MMC5983MA
  By: Nathan Seidle and Ricardo Ramos
  SparkFun Electronics
  Date: April 14th, 2022
  License: SparkFun code, firmware, and software is released under the MIT License(http://opensource.org/licenses/MIT).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/19034

  This example demonstrates how to compute a magnetic heading from the sensor over SPI

  Hardware Connections:
  Connect CIPO to MISO, COPI to MOSI, and SCK to SCK, on an Arduino.
  please check your board's pinout for these connections.
  orientation points to where its in the direction of the SCL pin on the MMC5983MA
*/

#include <SPI.h>
#include <sensors.h>

#include <SparkFun_MMC5983MA_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_MMC5983MA

SFE_MMC5983MA myMag;

//chip select pin
int csPin = 2;

const double bx = 3687.323025;
const double by = -27.369635;
const double bz = 12356.759856;

const double Ainv[3][3] = {
  { 0.006894, 0.000023, 0.000042 },
  { 0.000023,  0.007292, -0.000001 },
  { 0.000042, -0.000001,  0.006879 }
};


bool init_MMC()
{
    Serial.begin(115200);
    Serial.println("MMC5983MA Example");

    SPI.begin();

    while (myMag.begin(csPin) == false)
    {
        Serial.println("MMC5983MA did not respond. Retrying...");
        delay(500);
        myMag.softReset();
        delay(500);
    }

    Serial.println("MMC5983MA connected");

    myMag.softReset();
    return true;
}

void process_MMC(MAG_data &mag_data){
    //calibration values
    const double bx = 3687.323025;
    const double by = -27.369635;
    const double bz = 12356.759856;

const double Ainv[3][3] = {
  { 0.006894, 0.000023, 0.000042 },
  { 0.000023,  0.007292, -0.000001 },
  { 0.000042, -0.000001,  0.006879 }
};
   uint32_t rawValueX = 0;
    uint32_t rawValueY = 0;
    uint32_t rawValueZ = 0;
    double scaledX = 0;
    double scaledY = 0;
    double scaledZ = 0;
    double heading = 0;

    // Read all three channels simultaneously
    myMag.getMeasurementXYZ(&rawValueX, &rawValueY, &rawValueZ);

    // The magnetic field values are 18-bit unsigned. The _approximate_ zero (mid) point is 2^17 (131072).
    // Here we scale each field to +/- 1.0 to make it easier to calculate an approximate heading.
    //
    // Please note: to properly correct and calibrate the X, Y and Z channels, you need to determine true
    // offsets (zero points) and scale factors (gains) for all three channels. Futher details can be found at:
    // https://thecavepearlproject.org/2015/05/22/calibrating-any-compass-or-accelerometer-for-arduino/
    double x = (double)rawValueX - 131072.0 - bx;
    double y = (double)rawValueY - 131072.0 - by;
    double z = (double)rawValueZ - 131072.0 - bz;

// Apply soft-iron / scale / misalignment correction
    scaledX = Ainv[0][0]*x + Ainv[0][1]*y + Ainv[0][2]*z;
    scaledY = Ainv[1][0]*x + Ainv[1][1]*y + Ainv[1][2]*z;
    scaledZ = Ainv[2][0]*x + Ainv[2][1]*y + Ainv[2][2]*z;

  double norm = sqrt(
    scaledX * scaledX +
    scaledY * scaledY +
    scaledZ * scaledZ
);

    scaledX /= norm;
    scaledY /= norm;
    scaledZ /= norm;
    // Magnetic north is oriented with the Y axis
    // Convert the X and Y fields into heading using atan2 (Arc Tangent 2)
    heading = atan2(scaledX, 0 - scaledY);

    // atan2 returns a value between +PI and -PI
    // Convert to degrees
    heading /= PI;
    heading *= 180;
    heading += 180;

    Serial.print("Heading: ");
    Serial.println(mag_data.heading, 1);
    delay(100);
    return;
}