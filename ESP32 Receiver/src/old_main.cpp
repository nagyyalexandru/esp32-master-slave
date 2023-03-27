// #include <Arduino.h>

// #include "esp_now.h"
// #include "WiFi.h"
// #include "HTTPClient.h"
// #include "ESPAsyncWebServer.h"

// #include <SPI.h>
// #include <TFT_eSPI.h>
// #include "Adafruit_ILI9341.h"
// #include "Arduino_JSON.h"

// #include <EEPROM.h>
// #include "WebPage.h"
// #include "index.h"
// #include "dashboard.h"
// #include "TimeE.h"

// // include images headers
// #include "low_beam_on.h"
// #include "high_beam_on.h"
// #include "gas_station.h"
// #include "red_gas_station.h"

// #define INTERVAL 100
// #define EEPROM_SIZE 3
// #define HELPER_COLOR_BACKGROUND 0x4208
// #define HELPER_COLOR_TEXT 0x5350
// #define HELPER_COLOR_DANGER 0xF9A6

// #define BAR_GRAPH1_X 45
// #define BAR_GRAPH2_X 85
// #define BAR_GRAPH3_X 125
// #define BAR_GRAPH4_X 165
// #define BAR_GRAPHS_Y 301

// TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
// AsyncWebServer server(80);
// AsyncEventSource events("/events");
// JSONVar masterBoard;

// int TIME = 111;
// int copyTime;

// // Set the Master Board MAC Address
// uint8_t masterAddress[] = {0x40, 0x22, 0xD8, 0xEA, 0x91, 0xA0};

// // PMK and LMK keys
// static const char *PMK_KEY_STR = "PMK123";
// static const char *LMK_KEY_STR = "LMK123";

// // WiFi Credidentials
// const char *ssid = "TP-Link_8971";
// const char *password = "alexmada1";

// // Structure to keep the temperature and humidity data
// // Is also required in the client to be able to save the data directly
// typedef struct struct_message
// {
//   int id;
//   float temp;
//   float hum;
//   uint16_t speed;
//   uint8_t fuel;
//   uint8_t lowbeam;
//   uint8_t highbeam;
//   float distance;
//   int readingId;
// } struct_message;

// float oldTemp = 0;
// float oldHum = 0;
// uint16_t oldSpeed = 301;
// uint8_t oldFuel = 5;

// struct_message incomingReadings;
// static stSendTime HMI_stTimeValues;

// void HMI__vShowTime()
// {
//   String HMI__TimeToDisplay;
//   String HMI__ExtraZero = "0";
//   //````````````````````````````````````````````````````````````````````````````````````
//   Time_vSendTimeToHMI();
//   EEPROM.begin(EEPROM_SIZE);
//   EEPROM.get(0, HMI_stTimeValues);
//   //````````````````````````````````````````````````````````````````````````````````````
//   String HMI__seconds = "";
//   String HMI__minutes = "";
//   String HMI__Hours = "";
//   String oldMinutes = "";
//   if (HMI_stTimeValues.seconds < 10)
//   {
//     HMI__seconds += HMI__ExtraZero;
//     HMI__seconds += (String)(HMI_stTimeValues.seconds);
//   }
//   else
//   {
//     HMI__seconds += (String)HMI_stTimeValues.seconds;
//   }

//   if (HMI_stTimeValues.minutes < 10)
//   {
//     HMI__minutes += HMI__ExtraZero;
//     HMI__minutes += (String)HMI_stTimeValues.minutes;
//   }
//   else
//   {
//     HMI__minutes += (String)HMI_stTimeValues.minutes;
//   }
//   if (HMI_stTimeValues.hours < 10)
//   {
//     HMI__Hours += HMI__ExtraZero;
//     HMI__Hours += (String)HMI_stTimeValues.hours;
//   }
//   else
//   {
//     HMI__Hours += (String)HMI_stTimeValues.hours;
//   }

//   // tft.drawString(HMI__Hours + " : " + HMI__minutes + " : " + HMI__seconds, 6, 5, 2);
//   // tft.println("");
//   // tft.println(HMI__Hours + " : " + HMI__minutes + " : " + HMI__seconds);
//   if(HMI__minutes != oldMinutes)
//   {
//     tft.fillRect(0, 0, 60, 30, HELPER_COLOR_BACKGROUND);
//     tft.drawString(HMI__Hours + " : " + HMI__minutes, 6, 5, 2);
//     oldMinutes = HMI__minutes;
//   }
  
//   EEPROM.put(0, HMI_stTimeValues);
//   EEPROM.commit();
// }

// // callback function executed when data is received
// void OnRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
// {
//   char macStr[18];
//   Serial.print("Message received from: ");
//   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//   Serial.println(macStr);
//   memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));

//   // setting all the fields to put in JSON String variable
//   masterBoard["id"] = incomingReadings.id;
//   masterBoard["temperature"] = incomingReadings.temp;
//   masterBoard["humidity"] = incomingReadings.hum;
//   masterBoard["speed"] = incomingReadings.speed;
//   masterBoard["fuel"] = incomingReadings.fuel;
//   masterBoard["lowbeam"] = incomingReadings.lowbeam;
//   masterBoard["highbeam"] = incomingReadings.highbeam;
//   masterBoard["distance"] = incomingReadings.distance;
//   masterBoard["readingId"] = incomingReadings.readingId;

//   // create JSON String variable and store in it the received data
//   String masterBoardJsonString = JSON.stringify(masterBoard);

//   // After getting all the received data on the JSON String variable,
//   // send the data to the browser as a new event

//   events.send(masterBoardJsonString.c_str(), "new_message", millis());

//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   Serial.print("Temperature: ");
//   Serial.println(incomingReadings.temp);
//   Serial.print("Humidity: ");
//   Serial.println(incomingReadings.hum);
//   Serial.print("Speed: ");
//   Serial.println(incomingReadings.speed);
//   Serial.print("Fuel: ");
//   Serial.println(incomingReadings.fuel);
//   Serial.print("Distance: ");
//   Serial.println(incomingReadings.distance);
//   Serial.print("Low Beam: ");
//   if(!incomingReadings.lowbeam)
//   {
//     Serial.println("OFF");
//   }
//   else
//   {
//     Serial.println("ON");
//   }
//   Serial.print("High Beam: ");
//   if(!incomingReadings.highbeam)
//   {
//     Serial.println("OFF");
//   }
//   else
//   {
//     Serial.println("ON");
//   }
//   Serial.println("- - - - - - - -");

//   /* ----------------------------*/
//   // tft.fillRect(0, 0, 60, 30, HELPER_COLOR_BACKGROUND);
//   // tft.fillRect(180, 0, 60, 30, HELPER_COLOR_BACKGROUND);
//   /* Start displaying on LCD */
//   HMI__vShowTime();

//   if(incomingReadings.temp != oldTemp)
//   {
//   tft.fillRect(180, 0, 60, 30, HELPER_COLOR_BACKGROUND);
//   tft.drawString(String(incomingReadings.temp, 1), 187, 5, 2);
//   tft.drawCircle(222, 10, 2.5, TFT_WHITE);
//   tft.drawString("C", 227, 5, 2);
//   oldTemp = incomingReadings.temp;
//   }

//   tft.drawLine(0, 280, 1000, 280, TFT_WHITE);

//   tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
//   tft.drawString("E", 46, 285, 2);
//   tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
//   tft.drawString("F", 193, 285, 2);

//   // Display speedometer
//   tft.fillRect(90, 80, 80, 67, HELPER_COLOR_BACKGROUND);
//   tft.setTextColor(TFT_WHITE);
//   tft.drawString(String(incomingReadings.speed) + "     ", 90, 80, 6);
//   tft.drawString("km/h", 90, 125, 4);

//   if (incomingReadings.speed > 50 && incomingReadings.distance < 10)
//   {
//     tft.setTextColor(HELPER_COLOR_DANGER);
//     tft.drawString("PERICOL!", 67, 150, 4);
//   }
//   else tft.fillRect(59, 148, 130, 24, HELPER_COLOR_BACKGROUND); 

//   tft.setTextColor(TFT_WHITE);
//   switch (incomingReadings.fuel)
//   {
//   case 4:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     oldFuel = incomingReadings.fuel;
//     tft.pushImage(5, 283, 35, 35, gas_station);
//     break;
//   case 3:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     tft.pushImage(5, 283, 35, 35, gas_station);
//     break;
//   case 2:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     tft.pushImage(5, 283, 35, 35, gas_station);
//     break;
//   case 1:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     tft.pushImage(5, 283, 35, 35, gas_station);
//     break;
//   default:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     tft.pushImage(5, 283, 35, 35, red_gas_station);
//     break;
//   }

//   if(incomingReadings.lowbeam)
//   {
//     tft.pushImage(80, 235, 35, 35, low_beam_on);
//   }
//   else if(!incomingReadings.lowbeam)
//   {
//     tft.fillRect(80, 235, 35, 35, HELPER_COLOR_BACKGROUND);
//   }
//   if(incomingReadings.highbeam)
//   {
//   tft.pushImage(130, 235, 35, 35, high_beam_on);
//   }
//   else if(!incomingReadings.highbeam)
//   {
//     tft.fillRect(130, 235, 35, 35, HELPER_COLOR_BACKGROUND);
//   }
// }

// void setup()
// {
//   // Initialize Serial Monitor
//   Serial.begin(115200);
//   // Setting the Display
//   tft.begin();
//   tft.setSwapBytes(true);
//   tft.fillScreen(ILI9341_NAVY);
//   tft.setTextColor(ILI9341_WHITE);

//   // Set device as a Wi-Fi Station and Access Point simultaneously
//   // WiFi.mode(WIFI_STA);
//   WiFi.mode(WIFI_AP_STA);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi ..");
//   tft.print("Connecting ..");
//   tft.drawLine(0, 20, 1000, 20, TFT_WHITE);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     tft.print(".");
//     delay(1000);
//   }
//   Serial.print(" SUCCESS!");
//   Serial.println("");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());
//   Serial.println("- - - - - - - -");
//   tft.println("");
//   tft.println(WiFi.localIP());
//   tft.print("Waiting for sensor readings...");
//   delay(1000);

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK)
//   {
//     Serial.println("There was an error initializing ESP-NOW");
//     return;
//   }
//   // Setting the PMK key
//   esp_now_set_pmk((uint8_t *)PMK_KEY_STR);
//   // Register the master
//   esp_now_peer_info_t masterInfo = {};
//   memcpy(masterInfo.peer_addr, masterAddress, 6);
//   masterInfo.channel = 0;
//   // Setting the master device LMK key
//   for (uint8_t i = 0; i < 16; i++)
//   {
//     masterInfo.lmk[i] = LMK_KEY_STR[i];
//   }
//   masterInfo.encrypt = true;

//   // Add master
//   if (esp_now_add_peer(&masterInfo) != ESP_OK)
//   {
//     Serial.println("There was an error registering the master");
//     return;
//   }
  
//   tft.fillScreen(HELPER_COLOR_BACKGROUND);
//   HMI__vShowTime();

//   tft.drawString(String(incomingReadings.temp, 1), 187, 5, 2);
//   tft.drawCircle(222, 10, 2.5, TFT_WHITE);
//   tft.drawString("C", 227, 5, 2);

//   tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
//   tft.drawString("E", 46, 285, 2);
//   tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
//   tft.drawString("F", 193, 285, 2);

//   // Display speedometer
//   tft.drawString(String(incomingReadings.speed) + "   ", 90, 80, 6);
//   tft.drawString("km/h", 90, 125, 4);

//   switch (incomingReadings.fuel)
//   {
//   case 4:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     oldFuel = incomingReadings.fuel;
//     break;
//   case 3:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     break;
//   case 2:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     break;
//   case 1:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_WHITE);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     break;
//   default:
//     tft.fillRect(BAR_GRAPH1_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH2_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH3_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     tft.fillRect(BAR_GRAPH4_X, BAR_GRAPHS_Y, 35, 10, TFT_BLACK);
//     oldFuel = incomingReadings.fuel;
//     break;
//   }
//   // Once the ESP-Now protocol is initialized, we will register the callback function
//   // to be able to react when a package arrives in near to real time without pooling every loop.
//   esp_now_register_recv_cb(OnRecv);

//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/html", index_html); });

//   events.onConnect([](AsyncEventSourceClient *client)
//                    {
//     if(client->lastId()){
//       Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
//     }
//     // send event with message "hello!", id current millis
//     // and set reconnect delay to 1 second
//     client->send("hello!", NULL, millis(), INTERVAL); });
//   server.addHandler(&events);
//   server.begin();
// }
// void loop()
// {
//   static unsigned long lastEventTime = millis();
//   static const unsigned long EVENT_INTERVAL_MS = INTERVAL;
//   if ((millis() - lastEventTime) > EVENT_INTERVAL_MS)
//   {
//     events.send("ping", NULL, millis());
//     lastEventTime = millis();
//   }
// }

//   // tft.println("");
//   // tft.print("Temperature: ");
//   // tft.println(incomingReadings.temp);
//   // tft.println("");
//   // tft.print("Humidity: ");
//   // tft.println(incomingReadings.hum);
//   // tft.println("");
//   // tft.print("Speed: ");
//   // tft.print(incomingReadings.speed);
//   // tft.println(" km/h");
//   // tft.println("");
//   // tft.print("Fuel Level: ");
//   // tft.println(incomingReadings.fuel);
//   // oldTemp = incomingReadings.temp;
//   // oldHum = incomingReadings.hum;
//   // oldSpeed = incomingReadings.speed;
//   // oldFuel = incomingReadings.fuel;