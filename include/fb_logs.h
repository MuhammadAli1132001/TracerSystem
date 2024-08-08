#ifndef FIREBASE_H
#define FIREBASE_H

#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ"
#define DATABASE_URL "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app/"

void firebase_setup(void);
void temperature_humidity_firebase(float Temperature, float Humidity);
void current_voltage_capacity_to_firebase(void);
void check_button_status(void);

#endif
