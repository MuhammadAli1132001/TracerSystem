#include "googlesheetstorage.h"
// Google Project ID
#define PROJECT_ID "device-tracer-421211"

// Service Account's client email
#define CLIENT_EMAIL "tracer-system@device-tracer-421211.iam.gserviceaccount.com"

// Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC/30siFAhbbRDh\nhGSH+4QTJjNEW/3BGk4lM9Gs4RYuHEfKhBzvtCj8gzCm2IPwXu2LsQrC7U8sSWnS\necojpwS2s1DfbwBdUcE8UY8sbFEv1Tc2nz7KVVt7KapAYZAr+vXcKtP7Wli9zBLw\n0bSNPFR+404bacmn2HVDbPwmsSUoP4puRkulRR9M0N7WixDcSBEKmSn0F98m8rzs\nD6Fn98irk/nE0PG6B3EBr28AOvNmB8MGWnQK2llEbRY+ILDbnE3yyXWF2j2DT2dg\njeuHRafJM3N+WVqx6iPVmyPCFBAKAHvz6ZBEEd3GFQDf87pqfg32i2nBbc0NapIB\n4w0M80otAgMBAAECggEABYIKIhxOcRwcaUeSVeT+fEjocoSW2ug/vgmoHJJe6fad\n3k5p65JRwDiejkDrk1w7mCWo7WzqjOw+lsWFlqhra43nkG0bUZJ7PZlfHCNai/Ok\nS3PJgFLFoYTSAlnKow3n6OjB1Rau3XlHlz+DM1q8Ajh8PC/j6Lw/VtmAvjZE9CFy\nEQzdJeHiv9FPvB6jDnmCbB9imQt0fFA/h3J4WzeGSVLTBx61+XJpbBRI/06cTlKN\n8DheNT92m52p/otH61UwqU40+GE6AQ9yFrT+1kWkcsltlCrg5kPP4o7/Y5UOkgO+\n7VXcV04F2gTCp3QvZ9IVwLJ0Y1QWvzs6Rq7WBU5BgQKBgQDvEI6ksdCp6wYJkexb\nsa3voYqpYr9+oQmQ2gdkjfb9j61m0A30F+IE2k4ZVH0mtb+mRSdEyTWa+LkYblh3\n5C9rsVKgkQ3mUNSvm+YJvglTGUgfyyOwlTrzbqJmPUayy4Ynlv8beJpld2wKGM5K\nQ4nuP1W98jHfkWbQm77gU3jblQKBgQDNduaGdsLutZr+++fvzIshjRjWJR00GpW8\nKykag0uFJHVQGyuHIxdsuNZkmo8K+V9M0cJd2IxzfWDbrJegY8U95ucCgacvg+0i\ns4teWQuzJ5cXyrvHWS+IEvB+B43Abprb7Tprvv01iOgxK3RVqZAfVkwFYCIQOvmS\nVGQf0tdOOQKBgQC3SzKTA+LA5PnUDJX0F98MhAcUqCm6pS34abKRXmepMaf51Dte\nk5Evt1F6ClWKgH9YtFzPWJZJI7qHCNO72LCjGWoIwi6uD/uCST2u6o2rsQ6jkdTj\nZwez7XeGfCTgoTtSz2r5XRbEBTRI6YwBVJdEnDrZUAD9MTZra36F8HoRoQKBgDDN\nAugBIT+tZskVb/tm68zmRHXojs0nW1U8MyEW+kL/a9XA/k+0qAWsyU9P3pXOsTH/\nyFid7I4pw22pysHPsLOJOmk//kOs5BAP8RRRthOxXZPLFVq99iotxW1JwgNoweNm\nry+UR3QFtpCnL5SBF7g5uQi10qFkQI7e+IEOhRERAoGABkW/wMmDB4i2yT3JE3dg\nSOx+EIecH59u+p4bUsQ7QShJ0ehxEiscTivEzZB1kp4PpHFTv6o16JM46BGweuha\nVaiUVEBr8RMTyPalUicoH0wXvTUkfuQ/XAhvGr30suPBD5V7wz+8e59SFihdgmGh\nLNKxohg3RVmI+SJCw8d7Wpk=\n-----END PRIVATE KEY-----\n";
// The ID of the spreadsheet where you'll publish the data
const char spreadsheetId[] = "1AWZN7kUKkJgYx-Yge_lchwPGfz8lKuKe_qU58SuQZrk";

extern ESP_Google_Sheet_Client Gosheet;

unsigned long getTime() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return 0;
    }
    time(&now);
    return now;
}

void initializeGSheet() {
    // Configure time
    configTime(0, 0, "pool.ntp.org");

    Gosheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

    // Connect to Wi-Fi
    WiFi.setAutoReconnect(true);

    // Serial.print("Connecting to Wi-Fi");
    // while (WiFi.status() != WL_CONNECTED) {
    //     Serial.print(".");
    //     delay(1000);
    // }
    // Serial.println();
    // Serial.print("Connected with IP: ");
    // Serial.println(WiFi.localIP());
    // Serial.println();

    // Set the callback for Google API access token generation status (for debug only)
    Gosheet.setTokenCallback(tokenStatusCallback);

    // Set the seconds to refresh the auth token before expire (60 to 3540, default is 300 seconds)
    Gosheet.setPrerefreshSeconds(10 * 60);

    // Begin the access token generation for Google API authentication
    Gosheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

// void readAndappenLogs(void){
        
//         temp = dht_sensor.readTemperature();
//         humi = dht_sensor.readHumidity();
//         pres = random(0, 100);
//         altitude = random(0, 100);
//         longitude = random(100, 5000);
//         epochTime = getTime();

//         appendToGSheet(temp, humi, pres, altitude, longitude, epochTime);
//     // }
// }
bool appendToGSheet(float temp, float hum, float pres, float altitude, float longitude, unsigned long epochTime) {
    FirebaseJson response;

    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");

    FirebaseJson valueRange;

    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temp);
    valueRange.set("values/[2]/[0]", hum);
    valueRange.set("values/[3]/[0]", pres);
    valueRange.set("values/[4]/[0]", altitude);
    valueRange.set("values/[5]/[0]", longitude);

    bool success = Gosheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success) {
        response.toString(Serial, true);
        valueRange.clear();
    } else {
        Serial.println(Gosheet.errorReason());
    }
    Serial.println();
    Serial.println(ESP.getFreeHeap());

    return success;
}

void tokenStatusCallback(TokenInfo info){
    if (info.status == token_status_error) {
        Gosheet.printf("Token info: type = %s, status = %s\n", Gosheet.getTokenType(info).c_str(), Gosheet.getTokenStatus(info).c_str());
        Gosheet.printf("Token error: %s\n", Gosheet.getTokenError(info).c_str());
    } else {
        Gosheet.printf("Token info: type = %s, status = %s\n", Gosheet.getTokenType(info).c_str(), Gosheet.getTokenStatus(info).c_str());
    }
}