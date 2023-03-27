#include "Arduino.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "esp_now.h"
#include "esp_wifi.h"

#ifndef ESP_MESSAGES_h
#define ESP_MESSAGES_h
#define BOARD_ID 1

// Set the SLAVE MAC Address
static uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0xEB, 0x39, 0x54};

// Set the PMK and LMK keys
// static const char *PMK_KEY_STR = "PMK123";
// static const char *LMK_KEY_STR = "LMK123";
// static const String PMK_KEY = "PMK123";
// static const String LMK_KEY = "LMK123";

static String EEPROM_Read_PMK;
static String EEPROM_Read_LMK;

// Structure to keep the temperature and humidity data from a DHT sensor
typedef struct struct_message
{
  int id;
  float temp;
  float hum;
  uint16_t speed;
  uint8_t fuel;
  uint8_t lowbeam = 0;
  uint8_t highbeam = 0;
  float distance;
  int readingId;
} struct_message;

// Create a struct_message called myData
static struct_message myData;

static unsigned long previousMillis = 0; // Stores last time temperature was published
const long interval = 10;         // Interval at which to publish sensor readings

static unsigned int readingId = 0;

// Insert your SSID
constexpr char WIFI_SSID[] = "NETGEAR24";

int32_t getWiFiChannel(const char *ssid);

void Esp_Now_Setup();

void Esp_Now_Loop();

#endif