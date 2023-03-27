#include "Arduino.h"
#include "ESP_MESSAGES.h"
#include "ESP_MESSAGES_E.h"
#include "CommonDataE.h"
#include "EEPROM.h"
#include "EEPROM_Helper.h"
#include "TFT_Display.h"

#define ESP_MESSAGES_DEBUG

void Esp_Messages_Setup()
{
    // Initialize EEPROM Module for reading the private data (keys, passwords)
    EEPROM.begin(EEPROM_SIZE);

    // Write on EEPROM in 'production' phase
    // EEPROM_Write_String(EEPROM_PMK_ADDR, PMK_KEY);
    // EEPROM_Write_String(EEPROM_LMK_ADDR, LMK_KEY);

    EEPROM_Read_PMK = EEPROM_Read_String(EEPROM_PMK_ADDR);
    EEPROM_Read_LMK = EEPROM_Read_String(EEPROM_LMK_ADDR);

    const char *u8pmk = EEPROM_Read_PMK.c_str();
    const char *u8lmk = EEPROM_Read_LMK.c_str();

    // Setting up the TFT for Debugging
    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println("Initialize WiFi Connection");
    tft.drawLine(0, 30, 1000, 30, TFT_WHITE);

    // Setting up WiFi as Access Point and Station simoultaneously
    WiFi.mode(WIFI_AP_STA);
#ifdef ESP_MESSAGES_DEBUG
    // measure the time for the network scan
    unsigned long WiFiScanStartTime = millis();
#endif
    Serial.println("Scanning for networks...");
    int networks = WiFi.scanNetworks();

    if (networks == 0)
    {
        Serial.println("No networks found");
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.println("No networks found");
    }
    else
    {
#ifdef ESP_MESSAGES_DEBUG
        Serial.print(networks);
        Serial.println(" networks found");
#endif
        tft.setCursor(0, 45);
        tft.print(networks);
        tft.println(" networks found");
        tft.println(" ");
        for (int i = 0; i < networks; ++i)
        {
            // Print SSID and RSSI for each network found
            tft.print(i + 1);
            tft.print(": ");
            tft.print(WiFi.SSID(i));
            tft.print(" (");
            tft.print(WiFi.RSSI(i));
            tft.println(")");
#ifdef ESP_MESSAGES_DEBUG
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.println(")");
#endif
        }
    }
#ifdef ESP_MESSAGES_DEBUG
    unsigned long WiFiScanEndTime = millis();
    unsigned long WiFiScanResult = WiFiScanEndTime - WiFiScanStartTime;
    Serial.print("Scan execution time: ");
    Serial.print(WiFiScanResult);
    Serial.println("ms");
#endif
    // Trying to connect
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi . . .");
    tft.println(" ");
    tft.println(" ");
    tft.print("Connecting to WiFi . . .");

    while (WiFi.status() != WL_CONNECTED)
    {
        tft.print(" . ");
        Serial.print(" . ");
        delay(WIFI_CONNECTING_DELAY);
        timeout_counter++;
        if (timeout_counter >= CONNECTION_TIMEOUT)
        {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.println(" ");
            tft.println(" ");
            tft.println("Error connecting to WiFi...");
            tft.print("Restart");
            Serial.println("Error connecting to WiFi...");
            Serial.println("Restart");
            delay(ESP_RESTART_DELAY);
            ESP.restart();
        }
    }

    tft.println(" ");
    tft.println(" ");
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Connected!");
    tft.println(" ");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println("Local ESP32 IP Addresss: ");
    tft.println(" ");
    tft.println(WiFi.localIP());
    Serial.print(" SUCCESS!");
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("- - - - - - - -");
    delay(WIFI_CONNECTED_DELAY);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("There was an error initializing ESP-NOW");
        return;
    }

    // Setting the PMK key
    esp_now_set_pmk((uint8_t *)u8pmk);
    // Register the master
    esp_now_peer_info_t masterInfo = {};
    memcpy(masterInfo.peer_addr, masterAddress, 6);
    masterInfo.channel = 0;
    // Setting the master device LMK key
    for (uint8_t i = 0; i < 16; i++)
    {
        masterInfo.lmk[i] = u8lmk[i];
    }
    masterInfo.encrypt = true;

    // Add master
    if (esp_now_add_peer(&masterInfo) != ESP_OK)
    {
        Serial.println("There was an error registering the master");
        return;
    }

    // Once the ESP-Now protocol is initialized, we will register the callback function
    // to be able to react when a package arrives in near to real time without pooling every loop.
    esp_now_register_recv_cb(OnRecv);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });

    events.onConnect([](AsyncEventSourceClient *client)
                     {
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), INTERVAL); });
    server.addHandler(&events);
    server.begin();
}

void Esp_Messages_Loop()
{
    static unsigned long lastEventTime = millis();
    static const unsigned long EVENT_INTERVAL_MS = INTERVAL;
    if ((millis() - lastEventTime) > EVENT_INTERVAL_MS)
    {
        events.send("ping", NULL, millis());
        lastEventTime = millis();
    }
}

// callback function executed when data is received
void OnRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    char macStr[18];
    Serial.print("Message received from: ");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);
    memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));

    // give the incomming message to shared data
    CommonData_Set(CommonData_enIncommingData, &incomingReadings);

    // setting all the fields to put in JSON String variable
    masterBoard["id"] = incomingReadings.id;
    masterBoard["temperature"] = incomingReadings.temp;
    masterBoard["humidity"] = incomingReadings.hum;
    masterBoard["speed"] = incomingReadings.speed;
    masterBoard["fuel"] = incomingReadings.fuel;
    masterBoard["lowbeam"] = incomingReadings.lowbeam;
    masterBoard["highbeam"] = incomingReadings.highbeam;
    masterBoard["distance"] = incomingReadings.distance;
    masterBoard["readingId"] = incomingReadings.readingId;

    // create JSON String variable and store in it the received data
    // for the web server
    String masterBoardJsonString = JSON.stringify(masterBoard);

    // After getting all the received data on the JSON String variable,
    // send the data to the browser as a new event

    events.send(masterBoardJsonString.c_str(), "new_message", millis());
#ifdef ESP_MESSAGES_DEBUG
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Temperature: ");
    Serial.println(incomingReadings.temp);
    Serial.print("Humidity: ");
    Serial.println(incomingReadings.hum);
    Serial.print("Speed: ");
    Serial.println(incomingReadings.speed);
    Serial.print("Fuel: ");
    Serial.println(incomingReadings.fuel);
    Serial.print("Distance: ");
    Serial.println(incomingReadings.distance);
    Serial.print("Low Beam: ");
    if (!incomingReadings.lowbeam)
    {
        Serial.println("OFF");
    }
    else
    {
        Serial.println("ON");
    }
    Serial.print("High Beam: ");
    if (!incomingReadings.highbeam)
    {
        Serial.println("OFF");
    }
    else
    {
        Serial.println("ON");
    }
    Serial.println("- - - - - - - -");
#endif
}