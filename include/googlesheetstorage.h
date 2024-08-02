#ifndef googlesheetstorage_h
#define googlesheetstorage_h

#include <ESP_Google_Sheet_Client.h>

// Function prototypes
void initializeGSheet(void);
unsigned long getTime();
bool appendToGSheet(float temp, float hum, float pres, float alt, float longi, unsigned long epochTime);

#endif


