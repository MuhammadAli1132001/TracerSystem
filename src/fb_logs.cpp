#include "fb_logs.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
uint8_t capacity = 77;
uint8_t current = 20;
uint8_t voltage = 63;
uint8_t Kmrange = 140;
float_t Temp, Humi;
uint8_t led_status;

void firebase_setup() {
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase signup successful");
        signupOK = true;
    } else {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

}

void temperature_humidity_firebase(float Temperature, float Humidity) {
    if (Firebase.RTDB.setFloat(&fbdo, "dht/humidity", Humidity)) {
        Serial.print("\nHumidity: ");
        Serial.println(Humidity);
        Serial.println("\nPASSED to Firebase");
        Serial.print("\nPATH: ");
        Serial.print(fbdo.dataPath());
        Serial.print("  TYPE: ");
        Serial.print(fbdo.dataType());
    } else {
        Serial.println("\nFAILED");
        Serial.print("\nREASON: ");
        Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setInt(&fbdo, "dht/temperature", Temperature)) {
        Serial.print("\nTemperature: ");
        Serial.println(Temperature);
        Serial.println("\nPASSED to Firebase");
        Serial.print("\nPATH: ");
        Serial.print(fbdo.dataPath());
        Serial.print("\nTYPE: ");
        Serial.print(fbdo.dataType());
    } else {
        Serial.println("\nFAILED");
        Serial.print("\nREASON: ");
        Serial.print(fbdo.errorReason());
    }
}

void current_voltage_capacity_to_firebase() {

    if (Firebase.ready()) {
        if (Firebase.RTDB.setInt(&fbdo, "capacity", capacity)) {
            Serial.print("\nCapacity: ");
            Serial.println(capacity);
            Serial.println("\nPASSED to Firebase");
        } else {
            Serial.println("\nFAILED");
            Serial.print("\nREASON: ");
            Serial.print(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "current", current)) {
            Serial.print("\nCurrent: ");
            Serial.println(current);
            Serial.println("\nPASSED to Firebase");
        } else {
            Serial.println("\nFAILED");
            Serial.print("\nREASON: ");
            Serial.print(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "voltage", voltage)) {
            Serial.print("\nVoltage: ");
            Serial.println(voltage);
            Serial.println("\nPASSED to Firebase");
        } else {
            Serial.println("\nFAILED");
            Serial.print("\nREASON: ");
            Serial.print(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "kmrange", Kmrange)) {
            Serial.print("\nKmrange: ");
            Serial.println(Kmrange);
            Serial.println("\nPASSED to Firebase");
        } else {
            Serial.println("\nFAILED");
            Serial.print("\nREASON: ");
            Serial.print(fbdo.errorReason());
        }
    }
}

void check_button_status() {
    if (Firebase.ready()) {
        if (Firebase.RTDB.setInt(&fbdo, "led", led_status)) {
            Serial.print("\nLED Status: ");
            Serial.println(led_status);
            Serial.println("\nPASSED to Firebase");
        } else {
            Serial.println("\nFAILED");
            Serial.print("\nREASON: ");
            Serial.print(fbdo.errorReason());
        }
    }
}