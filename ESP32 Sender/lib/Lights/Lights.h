#ifndef Lights_h
#define Lights_h
#include "Arduino.h"

#define LOW_BEAM_BUTTON_PIN 18
#define HIGH_BEAM_BUTTON_PIN 19
#define LOW_BEAM_LED_PIN 22
#define HIGH_BEAM_LED_PIN 23
#define LOW_BEAM 0
#define HIGH_BEAM 1

static int lastButtonState[2] = {0, 0};    // the previous state of button
static int currentButtonState[2]; // the current state of button

static uint8_t u8LowBeamState;
static uint8_t u8HighBeamState;

void Lights_Setup();

void Lights_Loop();

uint8_t Lights_GetLowBeamState();
uint8_t Lights_GetHighBeamState();

#endif