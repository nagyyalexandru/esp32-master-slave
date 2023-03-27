#include "Arduino.h"
#include "ESP_MESSAGES.h"
#include "SharedDataE.h"
#include "Speed.h"
#include "Fuel.h"
#include "Lights.h"
#include "Temperature.h"
#include "Radar.h"
#include "EEPROM_Helper.h"
#include "EEPROM.h"

// #define ESP_NOW_DEBUG

int32_t getWiFiChannel(const char *ssid)
{
    if (int32_t n = WiFi.scanNetworks())
    {
        for (uint8_t i = 0; i < n; i++)
        {
            // compare the strings, if 0 then strings are the same
            if (!strcmp(ssid, WiFi.SSID(i).c_str()))
            {
                return WiFi.channel(i);
            }
        }
    }
    return 0;
}

// Callback to have a track of sent messages
void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nSend message status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully" : "Sent Failed");
}

void Esp_Now_Setup()
{
    EEPROM.begin(EEPROM_SIZE);
    // EEPROM_Write_String(EEPROM_PMK_ADDR, PMK_KEY);
    // EEPROM_Write_String(EEPROM_LMK_ADDR, LMK_KEY);
    
    EEPROM_Read_PMK = EEPROM_Read_String(EEPROM_PMK_ADDR);
    EEPROM_Read_LMK = EEPROM_Read_String(EEPROM_LMK_ADDR);

    const char *u8pmk = EEPROM_Read_PMK.c_str();
    const char *u8lmk= EEPROM_Read_LMK.c_str();

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    int32_t channel = getWiFiChannel(WIFI_SSID);

    // WiFi.printDiag(Serial); // Uncomment to verify channel number before
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
    // WiFi.printDiag(Serial); // Uncomment to verify channel change after

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("There was an error initializing ESP-NOW");
        return;
    }

    // Setting the PMK key
    //esp_now_set_pmk((uint8_t *)PMK_KEY_STR);
    esp_now_set_pmk((uint8_t *)u8pmk);

    // Register the slave
    esp_now_peer_info_t slaveInfo = {};
    memcpy(slaveInfo.peer_addr, broadcastAddress, 6);
    slaveInfo.channel = 0;

    // Setting the master device LMK key
    for (uint8_t i = 0; i < 16; i++)
    {
        slaveInfo.lmk[i] = u8lmk[i];
    }
    slaveInfo.encrypt = true;

    // Add slave
    if (esp_now_add_peer(&slaveInfo) != ESP_OK)
    {
        Serial.println("There was an error registering the slave");
        return;
    }

    // We will register the callback function to respond to the event
    esp_now_register_send_cb(OnSent);
}

void Esp_Now_Loop()
{
    // unsigned long currentMillis = millis();
    // if (currentMillis - previousMillis >= interval)
    // {
        // Save the last time a new reading was published
        // previousMillis = currentMillis;
        // Set values to send
        myData.id = BOARD_ID;
        myData.temp = Temperature_DHT_Sensor.readTemperature();
        myData.hum = Temperature_DHT_Sensor.readHumidity();
        myData.readingId = readingId++;
        myData.speed = Speed_GetValues();
        myData.fuel = Fuel_GetValues();
        myData.distance = Radar_GetDistance();
        myData.lowbeam = Lights_GetLowBeamState();
        myData.highbeam = Lights_GetHighBeamState();
        
        // Send message via ESP-NOW
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
#ifdef ESP_NOW_DEBUG
        Serial.print("Temp : ");
        Serial.println(myData.temp);
        Serial.print("Hum : ");
        Serial.println(myData.hum);
        Serial.print("Speed : ");
        Serial.println(myData.speed);
        Serial.print("Fuel : ");
        Serial.println(myData.fuel);
        Serial.print("distance : ");
        Serial.println(myData.distance);
        Serial.print("lowbeam : ");
        Serial.println(myData.lowbeam);
        Serial.print("highbeam : ");
        Serial.println(myData.highbeam);

        if (result == ESP_OK)
        {
            Serial.println("Sent with success");
        }
        else
        {
            Serial.println("Error sending the data");
        }
#endif
    //}
}