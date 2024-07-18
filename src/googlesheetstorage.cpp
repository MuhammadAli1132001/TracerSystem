#include "main.h"

const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC/30siFAhbbRDh\nhGSH+4QTJjNEW/3BGk4lM9Gs4RYuHEfKhBzvtCj8gzCm2IPwXu2LsQrC7U8sSWnS\necojpwS2s1DfbwBdUcE8UY8sbFEv1Tc2nz7KVVt7KapAYZAr+vXcKtP7Wli9zBLw\n0bSNPFR+404bacmn2HVDbPwmsSUoP4puRkulRR9M0N7WixDcSBEKmSn0F98m8rzs\nD6Fn98irk/nE0PG6B3EBr28AOvNmB8MGWnQK2llEbRY+ILDbnE3yyXWF2j2DT2dg\njeuHRafJM3N+WVqx6iPVmyPCFBAKAHvz6ZBEEd3GFQDf87pqfg32i2nBbc0NapIB\n4w0M80otAgMBAAECggEABYIKIhxOcRwcaUeSVeT+fEjocoSW2ug/vgmoHJJe6fad\n3k5p65JRwDiejkDrk1w7mCWo7WzqjOw+lsWFlqhra43nkG0bUZJ7PZlfHCNai/Ok\nS3PJgFLFoYTSAlnKow3n6OjB1Rau3XlHlz+DM1q8Ajh8PC/j6Lw/VtmAvjZE9CFy\nEQzdJeHiv9FPvB6jDnmCbB9imQt0fFA/h3J4WzeGSVLTBx61+XJpbBRI/06cTlKN\n8DheNT92m52p/otH61UwqU40+GE6AQ9yFrT+1kWkcsltlCrg5kPP4o7/Y5UOkgO+\n7VXcV04F2gTCp3QvZ9IVwLJ0Y1QWvzs6Rq7WBU5BgQKBgQDvEI6ksdCp6wYJkexb\nsa3voYqpYr9+oQmQ2gdkjfb9j61m0A30F+IE2k4ZVH0mtb+mRSdEyTWa+LkYblh3\n5C9rsVKgkQ3mUNSvm+YJvglTGUgfyyOwlTrzbqJmPUayy4Ynlv8beJpld2wKGM5K\nQ4nuP1W98jHfkWbQm77gU3jblQKBgQDNduaGdsLutZr+++fvzIshjRjWJR00GpW8\nKykag0uFJHVQGyuHIxdsuNZkmo8K+V9M0cJd2IxzfWDbrJegY8U95ucCgacvg+0i\ns4teWQuzJ5cXyrvHWS+IEvB+B43Abprb7Tprvv01iOgxK3RVqZAfVkwFYCIQOvmS\nVGQf0tdOOQKBgQC3SzKTA+LA5PnUDJX0F98MhAcUqCm6pS34abKRXmepMaf51Dte\nk5Evt1F6ClWKgH9YtFzPWJZJI7qHCNO72LCjGWoIwi6uD/uCST2u6o2rsQ6jkdTj\nZwez7XeGfCTgoTtSz2r5XRbEBTRI6YwBVJdEnDrZUAD9MTZra36F8HoRoQKBgDDN\nAugBIT+tZskVb/tm68zmRHXojs0nW1U8MyEW+kL/a9XA/k+0qAWsyU9P3pXOsTH/\nyFid7I4pw22pysHPsLOJOmk//kOs5BAP8RRRthOxXZPLFVq99iotxW1JwgNoweNm\nry+UR3QFtpCnL5SBF7g5uQi10qFkQI7e+IEOhRERAoGABkW/wMmDB4i2yT3JE3dg\nSOx+EIecH59u+p4bUsQ7QShJ0ehxEiscTivEzZB1kp4PpHFTv6o16JM46BGweuha\nVaiUVEBr8RMTyPalUicoH0wXvTUkfuQ/XAhvGr30suPBD5V7wz+8e59SFihdgmGh\nLNKxohg3RVmI+SJCw8d7Wpk=\n-----END PRIVATE KEY-----\n";

// Token Callback function
void tokenStatusCallback(TokenInfo info);

// dht 
DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
float temp;
float hum;
float pres;

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup_googlesheet(){

    Serial.begin(115200);
    Serial.println();
    Serial.println();

    //Configure time
    configTime(0, 0, ntpServer);

    // // Initialize BME280 sensor 
    // if (!bme.begin(0x76)) {
    //   Serial.println("Could not find a valid BME280 sensor, check wiring!");
    //   while (1);
    // }

    GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

    // Connect to Wi-Fi
    WiFi.setAutoReconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Set the callback for Google API access token generation status (for debug only)
    GSheet.setTokenCallback(tokenStatusCallback);

    // Set the seconds to refresh the auth token before expire (60 to 3540, default is 300 seconds)
    GSheet.setPrerefreshSeconds(10 * 60);

    // Begin the access token generation for Google API authentication
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop_googlesheet(){
    // Call ready() repeatedly in loop for authentication checking and processing
    bool ready = GSheet.ready();

    if (ready && millis() - lastTime > timerDelay){
        lastTime = millis();

        FirebaseJson response;

        Serial.println("\nAppend spreadsheet values...");
        Serial.println("----------------------------");

        FirebaseJson valueRange;

        // New BME280 sensor readings
        temp = dht_sensor.readTemperature();
        //temp = 1.8*bme.readTemperature() + 32;
        hum = dht_sensor.readHumidity();
        pres = 870/100.0F;
        // Get timestamp
        epochTime = getTime();

        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", epochTime);
        valueRange.set("values/[1]/[0]", temp);
        valueRange.set("values/[2]/[0]", hum);
        valueRange.set("values/[3]/[0]", pres);

        // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
        // Append values to the spreadsheet
        bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
        if (success){
            response.toString(Serial, true);
            valueRange.clear();
        }
        else{
            Serial.println(GSheet.errorReason());
        }
        Serial.println();
        Serial.println(ESP.getFreeHeap());
    }
}

void tokenStatusCallback(TokenInfo info){
    if (info.status == token_status_error){
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    }
    else{
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}