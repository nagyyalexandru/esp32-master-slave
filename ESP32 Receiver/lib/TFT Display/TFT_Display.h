#include "Arduino.h"
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "ESP_MESSAGES_E.h"

#ifndef TFT_Display_h
#define TFT_Display_h

#define BAR_GRAPH1_X 55
#define BAR_GRAPH2_X 95
#define BAR_GRAPH3_X 135
#define BAR_GRAPH4_X 175
#define BAR_GRAPHS_Y 307

#define TFT_LOADING_TIME 2000

static TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

static struct_message GetIncommingData;

void TFT_Display_Setup();
void TFT_Display_Loop();
void TFT_CheckReadings();
void displayTime();
void displayTemperature();
void displayLights();
void displayFuelBar();

#endif