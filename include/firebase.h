#ifndef firebase_h
#define firebase_h

#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define switch_pin 3
#define database_led 5

// Insert your network credentials


// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Insert Firebase project API Key
#define API_KEY "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ"
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app/"

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int count = 0;

uint8_t capacity = 90;
uint8_t current = 20;
uint8_t voltage = 63;
uint8_t Kmrange = 140;
float_t Temp, Humi;
uint8_t led_status;

void firebase_setup(void);
void temperature_humidity_firebase(float Temperature, float Humidity);
void current_voltage_capacity_to_firebase(void);
void check_button(void);
void check_button_status(void);

#endif