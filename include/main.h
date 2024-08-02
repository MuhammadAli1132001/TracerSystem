#ifndef Main_h
#define Main_h

#include <Arduino.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LittleFS.h>
#include "time.h"
#include "firebase.h"
// #if defined(ESP32)
#include <WiFi.h>
// #elif defined(ESP8266)
// #include <ESP8266WiFi.h>
// #endif

// Insert your network credentials
#define WIFI_SSID "CST WIFI"
#define WIFI_PASSWORD "iotdevs123"

#define DataSendedLed 8
#define WifiConnectedLed 7
#define Dht_Sensor_Pin 12
#define Dht_type DHT11

void File_handle(void);
void WiFi_setup(void);
void temperature_humidity_firebase(float Temperature, float Humidity);
void current_voltage_capacity_to_firebase(void);
void check_button(void);
#endif