#include "Arduino.h"

#ifndef ESP_MESSAGES_E_h
#define ESP_MESSAGES_E_h
// Structure to keep the temperature and humidity data
// Is also required in the client to be able to save the data directly
static struct struct_message
{
  int id;
  float temp;
  float hum;
  uint16_t speed;
  uint8_t fuel;
  uint8_t lowbeam;
  uint8_t highbeam;
  float distance;
  int readingId;
} incomingReadings;

#endif