#include "Arduino.h"
#ifndef Speed_h
#define Speed_h
#define SPEED_PIN 34

#define SPEED__IN_MIN 0
#define SPEED__IN_MAX 4095
#define SPEED__OUT_MIN 0
#define SPEED__OUT_MAX 300

static int SPEED_READ_VALUE = 0;
static uint16_t SPEED_VALUE;

void Speed_Setup();

void Speed_Loop();

uint16_t Speed_GetValues();

#endif