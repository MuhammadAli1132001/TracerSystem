#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LittleFS.h>
#include <WiFi.h>


#define WIFI_SSID "CST WIFI"
#define WIFI_PASSWORD "iotdevs123"

#define DataSendedLed 8
#define WifiConnectedLed 7
#define Dht_Sensor_Pin 12
#define Dht_type DHT11
#define switch_pin 3
#define database_led 5

void File_handle(void);
void WiFi_setup(void);
// void check_button(void);
void firebase_setup(void);
void temperature_humidity_firebase(float Temperature, float Humidity);
void current_voltage_capacity_to_firebase(void);
void check_button_status(void);

#endif
