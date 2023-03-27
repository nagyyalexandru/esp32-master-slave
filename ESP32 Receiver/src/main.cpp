#include <Arduino.h>
#include "TFT_Display.h"

#include "ESP_MESSAGES.h"
#include "CommonDataE.h"

void setup()
{
    // Initialize Serial Monitor
    Serial.begin(115200);
    CommonData_Setup();
    Esp_Messages_Setup();
    TFT_Display_Setup();
}

void loop()
{
    CommonData_ReadQueues();
    TFT_Display_Loop();
    Esp_Messages_Loop();
}