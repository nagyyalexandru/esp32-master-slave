#include "Arduino.h"
#include "TFT_Display.h"
#include "ESP_MESSAGES_E.h"

#ifndef Gauge_h
#define Gauge_h

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define GREEN2BLUE 6
#define ILI9341_GREY 0x2104 // Dark grey 16 bit colour

static uint32_t runTime = -99999;       // time for next update
static struct_message GetIncommingSpeed;
static int reading = 0; // Value to be displayed
static int d = 0; // Variable used for the sinewave test waveform

unsigned int rainbow(byte value);
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char const *units, byte scheme);
void Gauge_drawSpeedGauge();

#endif