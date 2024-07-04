#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

// #define DataSendedLed 8
// #define Dht_Sensor_Pin 12           //Read esp32 datasheet strapping pins section. 15 and more importantly 2 and 12 are strapping pins.
// #define switch_pin 3
// #define Dht_type DHT11

// float Humidity = 0.0;
// float Temperature = 0.0;

// DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
// uint8_t capacity = 90;
// uint8_t current = 25;
// uint8_t voltage = 63;

// void setup()
// {
//   Serial.begin(115200);
//   pinMode(Dht_Sensor_Pin, OUTPUT);
//   delay(1000);

// }

// void loop(){

//   // sendDataPrevMillis = millis();
//   Humidity = dht_sensor.readTemperature();
//   Temperature = dht_sensor.readHumidity();
//   digitalWrite(DataSendedLed, HIGH);

//   Serial.print("\nHumidity:  ");
//   Serial.println(Humidity);

//   Serial.print("\nTemperature:  ");
//   Serial.println(Temperature);

//   Serial.print("\nCapacity:  ");
//   Serial.println(capacity);
//   Serial.print("\nRandom Current:  ");

//   Serial.println(current);
//   Serial.print("\nRandom Voltage:  ");
//   Serial.println(voltage);
//   delay(3000);
// }


// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "CST WIFI"
#define WIFI_PASSWORD "iotdevs123"

// #define wifissid "CST WIFI"
// #define wifipssd "iotdevs123"
// Insert Firebase project API Key
#define API_KEY "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define DataSendedLed 8
#define WifiConnectedLed 7
#define Dht_Sensor_Pin 12
#define switch_pin 3
#define database_led 5

#define Dht_type DHT11
float Humidity = 0.0;
float Temperature = 0.0;

bool led_status = false;

DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
WebServer server(80);

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

uint8_t capacity = 90;
uint8_t current = 30;
uint8_t voltage = 63;
uint8_t Kmrange = 140;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  // pinMode(WifiConnectedLed, OUTPUT);
  // pinMode(DataSendedLed, OUTPUT);
  // pinMode(switch_pin, INPUT);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();

  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  digitalWrite(WifiConnectedLed, HIGH);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  // Firebase.reconnectWiFi(true);
}

void loop(){

  if (!digitalRead(switch_pin))
  {
    /* code */
    led_status = !led_status;
    Serial.print("button pressed led status is "); Serial.print(led_status);
    
  }
  
  if(!digitalRead(switch_pin))
  {
    if (Firebase.RTDB.getBool(&fbdo, "switch/led_status"))
    {
      
    }
  }
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    Humidity = dht_sensor.readTemperature();
    Temperature = dht_sensor.readHumidity();
    digitalWrite(DataSendedLed, HIGH);

    if (Firebase.RTDB.getBool(&fbdo, "switch/led_status"))
    {
      led_status = fbdo.boolData();
      digitalWrite(database_led, led_status);
    }
    else {
      Serial.print("switch is not getted");
    }
  
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "dht/humidity", Humidity))
    {

      Serial.print("\nHumidity:  ");
      Serial.println(Humidity);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("\nREASON: ");
      Serial.print(fbdo.errorReason());
    }

        // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "dht/temp", Temperature))
    {

      Serial.print("\nTemperature:  ");
      Serial.println(Temperature);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());

      Serial.print("\nTYPE:  ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }


    if (Firebase.RTDB.setFloat(&fbdo, "battery/capacity", capacity))
    {

      Serial.print("\nCapacity:  ");
      Serial.println(capacity);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("\nREASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/current", current))
    {

      Serial.print("\nRnadom Current:  ");
      Serial.println(current);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("\nREASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/voltage", voltage))
    {

      Serial.print("\nRandom Voltage:  ");
      Serial.println(current);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print(" TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("\nREASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/kmrange", Kmrange))
    {

      Serial.print("\nRandom Range:  ");
      Serial.println(current);
      Serial.println("\nPASSED to firebase");
      Serial.print("\nPATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print(" TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("\nFAILED");
      Serial.print("\nREASON: ");
      Serial.print(fbdo.errorReason());
    }
  }
}
