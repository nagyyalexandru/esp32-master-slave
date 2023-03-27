#include <DHT.h>
#include "Arduino.h"
#ifndef Temperature_h
#define Temperature_h

#define TEMPERATURE_DHT_PIN 5
#define TEMPERATURE_DHT_TYPE DHT11

static DHT Temperature_DHT_Sensor(TEMPERATURE_DHT_PIN, TEMPERATURE_DHT_TYPE);

void Temperature_Setup();
void Temperature_Loop();

#endif