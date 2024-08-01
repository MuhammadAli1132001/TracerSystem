#ifndef googlesheetstorage_h
#define googlesheetstorage_h

#include <ESP_Google_Sheet_Client.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// Function prototypes
void initializeGSheet();
bool appendToGSheet(float temp, float hum, float pres, float alt, float longi, unsigned long epochTime);
void tokenStatusCallback(TokenInfo info);
#endif


