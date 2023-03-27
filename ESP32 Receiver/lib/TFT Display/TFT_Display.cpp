#include "Arduino.h"
#include "TFT_Display.h"
#include "Gauge.h"
#include "CommonDataE.h"
// include images
#include "setup_background.h"
#include "low_beam_on.h"
#include "high_beam_on.h"
#include "gas_station.h"
#include "red_gas_station.h"

void TFT_Display_Setup()
{
    tft.begin();
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, 240, 320, setup_background);
    vTaskDelay(TFT_LOADING_TIME / portTICK_PERIOD_MS);
    tft.fillScreen(TFT_BLACK);
    Gauge_drawSpeedGauge();
    displayTime();
    displayTemperature();
    displayLights();
    displayFuelBar();
}

void TFT_Display_Loop()
{   
    Gauge_drawSpeedGauge();
    displayTime();
    displayTemperature();
    displayLights();
    displayFuelBar();
    TFT_CheckReadings();
}

void TFT_CheckReadings()
{
    CommonData_Get(CommonData_enIncommingData, &GetIncommingData);
    int _readingId = 0;
    if ((GetIncommingData.readingId - _readingId) == _readingId)
    {
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.drawString("No readings", 87, 213, 2);
    }
    else
    {
        tft.fillRect(85, 212, 80, 17, TFT_BLACK);
    }
}

void displayTime()
{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("15 : 30", 97, 168, 2);
}

void displayTemperature()
{
    float lastTempRead = 0;
    CommonData_Get(CommonData_enIncommingData, &GetIncommingData);
    if(lastTempRead != GetIncommingData.temp)
    {
    //tft.fillRect(98, 182, 45, 13, TFT_GREEN);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(String(GetIncommingData.temp, 1), 98, 184, 2);
    tft.drawString(" C", 128, 184, 2);
    lastTempRead = GetIncommingData.temp;
    }
}

void displayLights()
{
    CommonData_Get(CommonData_enIncommingData, &GetIncommingData);

    if (GetIncommingData.lowbeam)
    {
        tft.pushImage(80, 235, 35, 35, low_beam_on);
    }
    else if (!GetIncommingData.lowbeam)
    {
        tft.fillRect(80, 235, 35, 35, TFT_BLACK);
    }
    if (GetIncommingData.highbeam)
    {
        tft.pushImage(130, 235, 35, 35, high_beam_on);
    }
    else if (!GetIncommingData.highbeam)
    {
        tft.fillRect(130, 235, 35, 35, TFT_BLACK);
    }
}

void displayFuelBar()
{
    CommonData_Get(CommonData_enIncommingData, &GetIncommingData);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("E", 56, 289, 2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("F", 199, 289, 2);

    switch (GetIncommingData.fuel)
    {
    case 4:
        tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.pushImage(8, 286, 35, 35, gas_station);
        break;
    case 3:
        tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.pushImage(8, 286, 35, 35, gas_station);
        break;
    case 2:
        tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.pushImage(8, 286, 35, 35, gas_station);
        break;
    case 1:
        tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
        tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.pushImage(8, 286, 35, 35, gas_station);
        break;
    default:
        tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, ILI9341_GREY);
        tft.pushImage(8, 286, 35, 35, red_gas_station);
        break;
    }
}