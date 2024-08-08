#ifndef GOOGLE_SHEET_STORAGE_H
#define GOOGLE_SHEET_STORAGE_H

#include <ESP_Google_Sheet_Client.h>

void initializeGSheet(void);
unsigned long getTime();
bool appendToGSheet(float temp, float hum, float pres, float alt, float longi, unsigned long epochTime);
void tokenStatusCallback(TokenInfo info);
#endif
