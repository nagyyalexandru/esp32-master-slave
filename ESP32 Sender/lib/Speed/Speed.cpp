#include "Arduino.h"
#include "SharedDataE.h"
#include "Speed.h"

// #define SPEED_DEBUG

void Speed_Setup()
{
    pinMode(SPEED_PIN, INPUT); // Optional
}

void Speed_Loop()
{
    SPEED_READ_VALUE = analogRead(SPEED_PIN);
    SPEED_VALUE = map(SPEED_READ_VALUE, SPEED__IN_MIN, SPEED__IN_MAX, SPEED__OUT_MAX, SPEED__OUT_MIN);

    #ifdef SPEED_DEBUG
    Serial.print("Speed : ");
    Serial.println(SPEED_VALUE);
    #endif
}

uint16_t Speed_GetValues()
{
    SPEED_READ_VALUE = analogRead(SPEED_PIN);
    SPEED_VALUE = map(SPEED_READ_VALUE, SPEED__IN_MIN, SPEED__IN_MAX, SPEED__OUT_MAX, SPEED__OUT_MIN);
    return SPEED_VALUE;
}