#include "Arduino.h"
#include "SharedDataE.h"
#include "Fuel.h"
// #define FUEL_DEBUG

void Fuel_Setup()
{
    pinMode(FUEL_PIN, INPUT); // Optional
}

void Fuel_Loop()
{
    pot_2_value = analogRead(FUEL_PIN);

    if (pot_2_value >= FUEL__ZERO && pot_2_value <= FUEL__LVL0 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH0; // low FUEL, 0 cells filled
    }
    else if (pot_2_value > FUEL__LVL0 && pot_2_value <= FUEL__LVL1 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH1; // 1 cell filled
    }
    else if (pot_2_value > FUEL__LVL1 && pot_2_value <= FUEL__LVL2 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH2; // 2 cells filled
    }
    else if (pot_2_value > FUEL__LVL2 && pot_2_value <= FUEL__LVL3 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH3; // 3 cells filled
    }
    else if (pot_2_value > FUEL__LVL3 && pot_2_value <= FUEL__LVL4 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH4; // 4 cells filled
    }
#ifdef FUEl_DEBUG
    Serial.print("Fuel Level : ");
    Serial.println(fuelLevel);
#endif
}

uint8_t Fuel_GetValues()
{
    pot_2_value = analogRead(FUEL_PIN);

    if (pot_2_value >= FUEL__ZERO && pot_2_value <= FUEL__LVL0 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH0; // low FUEL, 0 cells filled
    }
    else if (pot_2_value > FUEL__LVL0 && pot_2_value <= FUEL__LVL1 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH1; // 1 cell filled
    }
    else if (pot_2_value > FUEL__LVL1 && pot_2_value <= FUEL__LVL2 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH2; // 2 cells filled
    }
    else if (pot_2_value > FUEL__LVL2 && pot_2_value <= FUEL__LVL3 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH3; // 3 cells filled
    }
    else if (pot_2_value > FUEL__LVL3 && pot_2_value <= FUEL__LVL4 + FUEL__THRESHOLD_UP)
    {
        fuelLevel = FUEL_BAGGRAPH4; // 4 cells filled
    }

    return fuelLevel;
}