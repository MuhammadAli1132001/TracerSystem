#include "firebase.h"

void firebase_setup()
{
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
        Serial.print("REASON: ");
        Serial.print(fbdo.errorReason());
    }
}

void current_voltage_capacity_to_firebase() {
    if (Firebase.RTDB.setFloat(&fbdo, "battery/capacity", capacity)) {
        Serial.print("\nCapacity: ");
        Serial.println(capacity);
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

    if (Firebase.RTDB.setFloat(&fbdo, "battery/current", current)) {
        Serial.print("\nRandom Current: ");
        Serial.println(current);
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

    if (Firebase.RTDB.setFloat(&fbdo, "battery/voltage", voltage)) {
        Serial.print("\nRandom Voltage: ");
        Serial.println(current);
        Serial.println("\nPASSED to Firebase");
        Serial.print("\nPATH: ");
        Serial.print(fbdo.dataPath());
        Serial.print(" TYPE: ");
        Serial.print(fbdo.dataType());
    } else {
        Serial.println("\nFAILED");
        Serial.print("\nREASON: ");
        Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/kmrange", Kmrange)) {
        Serial.print("\nRandom Range: ");
        Serial.println(current);
        Serial.println("\nPASSED to Firebase");
        Serial.print("\nPATH: ");
        Serial.print(fbdo.dataPath());
        Serial.print(" TYPE: ");
        Serial.print(fbdo.dataType());
    } else {
        Serial.println("\nFAILED");
        Serial.print("\nREASON: ");
        Serial.print(fbdo.errorReason());
    }
}

void check_button() {

    if (!digitalRead(switch_pin)) {
        led_status = !led_status;
        Serial.print("Button pressed to change LED status to ");
        Serial.print(led_status);
    }
}

void check_button_status()
{
    if (Firebase.RTDB.getBool(&fbdo, "switch/led_status")) {
        led_status = fbdo.boolData();
        digitalWrite(database_led, led_status);

    }else{
        Serial.print("Failed to get switch status");
        }
}