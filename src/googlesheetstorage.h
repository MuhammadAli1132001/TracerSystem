#ifndef google_sheet
#define google_sheet


// Google Project ID
#define PROJECT_ID "device-tracer-421211"
#define Dht_Sensor_Pin 12
// Service Account's client email
#define CLIENT_EMAIL "tracer-system@device-tracer-421211.iam.gserviceaccount.com"
#define Dht_type DHT11
// Service Account's private key

// The ID of the spreadsheet where you'll publish the data
const char spreadsheetId[] = "1AWZN7kUKkJgYx-Yge_lchwPGfz8lKuKe_qU58SuQZrk";


// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";

// Variable to save current epoch time
unsigned long epochTime; 
// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 30000;

void loop_googlesheet();
void setup_googlesheet();

#endif