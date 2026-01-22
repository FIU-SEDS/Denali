#include <Arduino.h>
#include <SPI.h>
#include "sensors.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        delay(10); // Wait for Serial on Teensy

    Serial.println("Initializing sensors...");

    SPI.begin();

    if (!init_bme())
    {
        Serial.println("BME initialization failed!");
    }

    Serial.println("BME initialized successfully");
}

void loop()
{
    BME_data baro;
    test_BME(baro);
    delay(1000);

    // Use process_bme for validated readings

    // if (process_bme(baro)) {
    //     Serial.print("Temperature = ");
    //     Serial.print(baro.temp);
    //     Serial.println(" °C");

    //     Serial.print("Pressure = ");
    //     Serial.print(baro.pressure);
    //     Serial.println(" hPa");

    //     Serial.print("Altitude = ");
    //     Serial.print(baro.altitude);
    //     Serial.println(" ft");

    //     Serial.print("Humidity = ");
    //     Serial.print(baro.humidity);
    //     Serial.println(" %");

    //     Serial.println();
    // } else {
    //     Serial.println("BME reading validation failed!");
    // }
}
