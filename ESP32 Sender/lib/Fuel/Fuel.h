#include "Arduino.h"

#ifndef Fuel_h
#define Fuel_h

#define FUEL_PIN 35

#define FUEL__THRESHOLD_UP 100
#define FUEL__THRESHOLD_DOWN 50
#define FUEL__ZERO 0
#define FUEL__FIVE 5
#define FUEL__LVL0 819
#define FUEL__LVL1 1638
#define FUEL__LVL2 2457
#define FUEL__LVL3 3276
#define FUEL__LVL4 4095
#define FUEL_BAGGRAPH0 0
#define FUEL_BAGGRAPH1 1
#define FUEL_BAGGRAPH2 2
#define FUEL_BAGGRAPH3 3
#define FUEL_BAGGRAPH4 4

static int pot_2_value = 0;
static uint8_t fuelLevel = 0;

void Fuel_Setup();

void Fuel_Loop();

uint8_t Fuel_GetValues();

#endif