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

// // Set the SLAVE MAC Address
// uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0xEB, 0x39, 0x54};

// // PMK and LMK keys
// static const char *PMK_KEY_STR = "PMK123";
// static const char *LMK_KEY_STR = "LMK123";

// // Structure to keep the temperature and humidity data from a DHT sensor
// typedef struct struct_message
// {
//   int id;
//   float temp;
//   float hum;
//   uint16_t speed;
//   uint8_t fuel;
//   uint8_t lowbeam = 0;
//   uint8_t highbeam = 0;
//   float distance;
//   int readingId;
// } struct_message;

// // Create a struct_message called myData
// struct_message myData;

// unsigned long previousMillis = 0; // Stores last time temperature was published
// const long interval = 50;         // Interval at which to publish sensor readings

// unsigned int readingId = 0;

// // Insert your SSID
// constexpr char WIFI_SSID[] = "TP-Link_8971";

// int32_t getWiFiChannel(const char *ssid)
// {
//   if (int32_t n = WiFi.scanNetworks())
//   {
//     for (uint8_t i = 0; i < n; i++)
//     {
//       if (!strcmp(ssid, WiFi.SSID(i).c_str()))
//       {
//         return WiFi.channel(i);
//       }
//     }
//   }
//   return 0;
// }

// // Callback to have a track of sent messages
// void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status)
// {
//   Serial.print("\r\nSend message status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully" : "Sent Failed");
// }

// void setup()
// {
//   // Init Serial Monitor
//   Serial.begin(115200);

//   // Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);
//   int32_t channel = getWiFiChannel(WIFI_SSID);

//   WiFi.printDiag(Serial); // Uncomment to verify channel number before
//   esp_wifi_set_promiscuous(true);
//   esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
//   esp_wifi_set_promiscuous(false);
//   WiFi.printDiag(Serial); // Uncomment to verify channel change after

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK)
//   {
//     Serial.println("There was an error initializing ESP-NOW");
//     return;
//   }

//   // Setting the PMK key
//   esp_now_set_pmk((uint8_t *)PMK_KEY_STR);

//   // Register the slave
//   esp_now_peer_info_t slaveInfo = {};
//   memcpy(slaveInfo.peer_addr, broadcastAddress, 6);
//   slaveInfo.channel = 0;
//   // Setting the master device LMK key
//   for (uint8_t i = 0; i < 16; i++)
//   {
//     slaveInfo.lmk[i] = LMK_KEY_STR[i];
//   }
//   slaveInfo.encrypt = true;

//   // Add slave
//   if (esp_now_add_peer(&slaveInfo) != ESP_OK)
//   {
//     Serial.println("There was an error registering the slave");
//     return;
//   }

//   // We will register the callback function to respond to the event
//   esp_now_register_send_cb(OnSent);
// }

// void loop()
// {

//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval)
//   {
//     // Save the last time a new reading was published
//     previousMillis = currentMillis;
//     // Set values to send
//     myData.id = BOARD_ID;
//     // myData.temp = Temperature_DHT_Sensor.readTemperature();
//     // myData.hum = Temperature_DHT_Sensor.readHumidity();
//     // myData.readingId = readingId++;
//     // myData.speed = map(pot_1_value, 0, 4095, 300, 0);
//     // myData.fuel = fuelLevel;
//     // myData.distance = distanceCm;

//     // Send message via ESP-NOW
//     esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
//     if (result == ESP_OK)
//     {
//       Serial.println("Sent with success");
//     }
//     else
//     {
//       Serial.println("Error sending the data");
//     }
//   }
// }
