#include "main.h"
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ"
#define DATABASE_URL "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
uint8_t capacity = 90;
uint8_t current = 20;
uint8_t voltage = 63;
uint8_t Kmrange = 140;
float_t Temp, Humi;
uint8_t led_status;

// DHT sensor
DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
WebServer server(80);

// Variables for sensor data
float temp;
float humi;
float pres;
float longitude, altitude;
unsigned long sendDataPrevMillis = 0;

void setup() {
    Serial.begin(115200);
    pinMode(DataSendedLed, OUTPUT);
    pinMode(switch_pin, INPUT);
    pinMode(database_led, OUTPUT);
    
    WiFi_setup();
    File_handle();
    firebase_setup();
    dht_sensor.begin();
}

void loop() {

    // check_button();

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();

        temp = dht_sensor.readTemperature();
        humi = dht_sensor.readHumidity();
        digitalWrite(DataSendedLed, HIGH);

        temperature_humidity_firebase(temp, humi);
        current_voltage_capacity_to_firebase();
        check_button_status();

    }
}

void File_handle()
{
    if (!LittleFS.begin(true)) {
        Serial.print("Error occurred while mounting LittleFS");
        return;
    }

    File file = LittleFS.open("/data.txt");
    if (!file) {
        Serial.print("Can't open the file");
    }

    Serial.print("File contents are:");
    while (file.available()) {
        Serial.write(file.read());
    }
    Serial.print("Read and closed");
    file.close();
}


void WiFi_setup() {

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();

    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    digitalWrite(WifiConnectedLed, HIGH);
}

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