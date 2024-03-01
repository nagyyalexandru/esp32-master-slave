#include "Arduino.h"
#include "Fuel.h"
#include "Speed.h"
#include "Lights.h"
#include "Radar.h"
#include "Temperature.h"
#include "ESP_MESSAGES.h"
#include "SharedDataE.h"

void setup()
{
  Serial.begin(115200);
  // Init the setup phase of all modules
  SharedData_Setup();
  Fuel_Setup();
  Lights_Setup();
  Radar_Setup();
  Speed_Setup();
  Temperature_Setup();
  Esp_Now_Setup();
}

void loop()
{
  SharedData_ReadQueues();
  Esp_Now_Loop();
}
