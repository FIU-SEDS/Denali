// This is for Arduino IDE
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
  Connect CS to pin 4 on an Arduino.
*/
#include <Arduino.h>
#include <SPI.h>
#include <SparkFun_MMC5983MA_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_MMC5983MA

SFE_MMC5983MA myMag;
//these are examples values - you must perform your own calibration
// Hard-iron offsets (from calibration)
// if performing calibration, use https://www.pjrc.com/store/prop_shield.html and download 
// the motionCal software to get hard-iron and soft-iron values
// if confused, use this repo for source code of MMC598MA https://github.com/sparkfun/SparkFun_MMC5983MA_Magnetometer_Arduino_Library
// this is to understand how to calibrate the magnetometer https://www.digikey.com/en/maker/projects/how-to-calibrate-a-magnetometer/50f6bc8f36454a03b664dca30cf33a8b

//put in values you determined from calibration here
//Hard-iron offsets
double magOffsetX = 1234.5;
double magOffsetY = -987.6;
double magOffsetZ = 432.1;

// Soft-iron scale factors
double magScaleX = 1.02;
double magScaleY = 0.98;
double magScaleZ = 1.01;

//
int csPin = 4;

void setup()
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
}

void loop()
{
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
    double x = (double)rawValueX - 131072.0;
    double y = (double)rawValueY - 131072.0;
    double z = (double)rawValueZ - 131072.0;

// Apply hard-iron offsets
    x -= magOffsetX;
    y -= magOffsetY;
    z -= magOffsetZ;

// Apply soft-iron scaling
    x *= magScaleX;
    y *= magScaleY;
    z *= magScaleZ;

// Assign to scaled variables for heading math
    scaledX = x;
    scaledY = y;
    scaledZ = z;

    // Magnetic north is oriented with the Y axis
    // Convert the X and Y fields into heading using atan2 (Arc Tangent 2)
    heading = atan2(scaledX, 0 - scaledY);

    // atan2 returns a value between +PI and -PI
    // Convert to degrees
    heading /= PI;
    heading *= 180;
    heading += 180;

    Serial.print("Heading: ");
    Serial.println(heading, 1);
    delay(100);
}