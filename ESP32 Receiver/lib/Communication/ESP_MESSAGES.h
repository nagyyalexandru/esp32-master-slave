#include "Arduino.h"

#ifndef ESP_MESSAGES_h
#define ESP_MESSAGES_h

#include "esp_now.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include "ESPAsyncWebServer.h"
#include "Arduino_JSON.h"
#include "index.h"

#define WIFI_SETUP_BGCOLOR 0x0007
#define INTERVAL 100
#define CONNECTION_TIMEOUT 8
#define WIFI_CONNECTING_DELAY 900
#define ESP_RESTART_DELAY 900
#define WIFI_CONNECTED_DELAY 2000

// Set the Master Board MAC Address
static uint8_t masterAddress[] = {0x40, 0x22, 0xD8, 0xEA, 0x91, 0xA0};

// PMK and LMK keys
// static const char *PMK_KEY_STR = "PMK123";
// static const char *LMK_KEY_STR = "LMK123";
// static const String PMK_KEY = "PMK123";
// static const String LMK_KEY = "LMK123";

// WiFi Credidentials for the web page
static const char *ssid = "NETGEAR24";
static const char *password = "netgear24";

static AsyncWebServer server(80);
static AsyncEventSource events("/events");
static JSONVar masterBoard;

static uint8_t timeout_counter = 0;

void OnRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

void Esp_Messages_Setup();

void Esp_Messages_Loop();


#endif