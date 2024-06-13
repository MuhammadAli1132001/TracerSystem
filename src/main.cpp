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
#define Dht_Sensor_Pin 9

#define Dht_type DHT11
float Humidity = 0.0;
float Temperature = 0.0;

DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
WebServer server(80);

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

uint8_t capacity = 60;
uint8_t current = 25;
uint8_t voltage = 63;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  pinMode(WifiConnectedLed, OUTPUT);
  pinMode(DataSendedLed, OUTPUT);

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
  Firebase.reconnectWiFi(true);
}

void loop()
{

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {

    sendDataPrevMillis = millis();
    Humidity = dht_sensor.readTemperature();
    Temperature = dht_sensor.readHumidity();
    digitalWrite(DataSendedLed, HIGH);

    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setFloat(&fbdo, "dht/temperature", Temperature))
    {

      Serial.print("  Temperature:  ");
      Serial.println(Temperature);
      Serial.println("PASSED");
      Serial.print(" PATH: ");
      Serial.print(fbdo.dataPath());

      Serial.print("  TYPE:  ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "dht/humidity", Humidity))
    {

      Serial.print("  Humidity:  ");
      Serial.println(Humidity);
      Serial.println("PASSED");
      Serial.print(" PATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/capacity", capacity))
    {

      Serial.print("  Capacity:  ");
      Serial.println(capacity);
      Serial.println("PASSED");
      Serial.print(" PATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/current", current))
    {

      Serial.print("  current:  ");
      Serial.println(current);
      Serial.println("PASSED");
      Serial.print(" PATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "battery/voltage", voltage))
    {

      Serial.print("  voltage:  ");
      Serial.println(current);
      Serial.println("PASSED");
      Serial.print(" PATH: ");
      Serial.print(fbdo.dataPath());
      Serial.print("  TYPE: ");
      Serial.print(fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.print("REASON: ");
      Serial.print(fbdo.errorReason());
    }
  }
}

// #define wifissid "CST WIFI"
// #define wifipssd "iotdevs123"
// #define led 2

// void handleOnroot();
// void handleOnNotFound();
// uint8_t H, T;
// WebServer Server(80);

// void setup() {

//   WiFi.mode(WIFI_STA);
//   WiFi.begin(wifissid,wifipssd);
//   Serial.begin(9600);

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(100);
//     Serial.print(".");
//   }

//   Serial.print("\nConnected to ");
//   Serial.print(wifissid);
//   Serial.print(" with local ip ");
//   Serial.print(WiFi.localIP());

//   Server.begin();
//   Server.on("/", handleOnroot);

//   Server.onNotFound(handleOnNotFound);

// }

// void loop() {

//   Server.handleClient();
//   delay(500);

// }

// void handleOnroot() {
//   digitalWrite(led, 1);
//   char temp[800];

//   H = random();
//   T = random();

//   snprintf(temp, 800,
//   "<html>\
//   <head>\
//     <meta http-equiv='refresh' content='5'/>\
//     <title>ESP32 Demo</title>\
//     <style>\
//       body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
//     </style>\
//   </head>\
//   <body>\
//   </body>\
// </html>",
//            H, T
//           );
//   Server.send(500, "text/html", temp);
//   digitalWrite(led, 0);
// }

// void handleOnNotFound() {
//   digitalWrite(led, 1);
//   String message = "File Not Found bro\n\n";
//   message += "URI: ";
//   message += Server.uri();
//   message += "\nMethod: ";
//   message += (Server.method() == HTTP_GET) ? "GET" : "POST";
//   message += "\nArguments: ";
//   message += Server.args();
//   message += "\n";

//   for (uint8_t i = 0; i < Server.args(); i++) {
//     message += " " + Server.argName(i) + ": " + Server.arg(i) + "\n";
//   }

//   Server.send(404, "text/plain", message);
//   digitalWrite(led, 0);
// }

// void returnfalse(){

// }