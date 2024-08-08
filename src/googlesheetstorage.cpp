#include "googlesheetstorage.h"

#define PROJECT_ID "device-tracer-421211"
#define CLIENT_EMAIL "tracer-system@device-tracer-421211.iam.gserviceaccount.com"

const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC/30siFAhbbRDh\n..."; // Truncated for brevity
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
    configTime(0, 0, "pool.ntp.org");

    Gosheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
    WiFi.setAutoReconnect(true);
    Gosheet.setTokenCallback(tokenStatusCallback);
    Gosheet.setPrerefreshSeconds(10 * 60);
    Gosheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

bool appendToGSheet(float temp, float hum, float pres, float alt, float longi, unsigned long epochTime) {
    FirebaseJson response;

    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");

    FirebaseJson valueRange;
    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temp);
    valueRange.set("values/[2]/[0]", hum);
    valueRange.set("values/[3]/[0]", pres);
    valueRange.set("values/[4]/[0]", alt);
    valueRange.set("values/[5]/[0]", longi);

    bool success = Gosheet.values.append(&response, spreadsheetId, "Sheet1!A1", &valueRange);
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

void tokenStatusCallback(TokenInfo info) {
    if (info.status == token_status_error) {
        Gosheet.printf("Token info: type = %s, status = %s\n", Gosheet.getTokenType(info).c_str(), Gosheet.getTokenStatus(info).c_str());
        Gosheet.printf("Token error: %s\n", Gosheet.getTokenError(info).c_str());
    } else {
        Gosheet.printf("Token info: type = %s, status = %s\n", Gosheet.getTokenType(info).c_str(), Gosheet.getTokenStatus(info).c_str());
    }
}
