#include "Arduino.h"
#include "Temperature.h"

void Temperature_Setup()
{
    Temperature_DHT_Sensor.begin();
}

void Temperature_Loop()
{
    // Serial.println(Temperature_DHT_Sensor.readTemperature());
}