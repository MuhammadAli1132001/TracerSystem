#ifndef Main_h
#define Main_h

#include <Arduino.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LittleFS.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
// For SD/SD_MMC mounting helper
// #include <GS_SDHelper.h>
#include "googlesheetstorage.h"

// #if defined(ESP32)
#include <WiFi.h>
// #elif defined(ESP8266)
// #include <ESP8266WiFi.h>
// #endif
// #include <Firebase_ESP_Client.h>

// Provide the token generation process info.
// #include "addons/TokenHelper.h"
// // Provide the RTDB payload printing info and other helper functions.
// #include "addons/RTDBHelper.h"

#include "googlesheetstorage.h"

// Insert your network credentials
#define WIFI_SSID "CST WIFI"
#define WIFI_PASSWORD "iotdevs123"


// // Insert Firebase project API Key
// #define API_KEY "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ"
// // Insert RTDB URLefine the RTDB URL */
// #define DATABASE_URL "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define DataSendedLed 8
#define WifiConnectedLed 7
#define Dht_Sensor_Pin 12
#define switch_pin 3
#define database_led 5
#define Dht_type DHT11

// uint8_t capacity = 90;
// uint8_t current = 20;
// uint8_t voltage = 63;
// uint8_t Kmrange = 140;

void WiFi_setup();
void temperature_humidity_firebase(float Temperature, float Humidity);
void current_voltage_capacity_to_firebase();
void check_button();
unsigned long getTime();
#endif