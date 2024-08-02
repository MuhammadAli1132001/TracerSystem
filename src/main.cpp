#include "main.h"
#include "googlesheetstorage.h"

ESP_Google_Sheet_Client Gosheet;

// DHT sensor
DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
WebServer server(80);

// Variables for sensor data
float temp;
float humi;
float pres;
float longitude, altitude;
unsigned long epochTime;

const char* ntpServer = "pool.ntp.org";

void setup() {
    Serial.begin(115200);
    pinMode(DataSendedLed, OUTPUT);
    pinMode(switch_pin, INPUT);
    pinMode(database_led, OUTPUT);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    File_handle();
    WiFi_setup();

    initializeGSheet();
    dht_sensor.begin();
}

void loop() {

    check_button();

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();

        temp = dht_sensor.readTemperature();
        humi = dht_sensor.readHumidity();
        digitalWrite(DataSendedLed, HIGH);

        temperature_humidity_firebase(temp, humi);
        current_voltage_capacity_to_firebase();
        check_button_status();

    }

    bool ready = Gosheet.ready();
    if (ready && millis() - lastTime > timerDelay) {
        lastTime = millis();

        temp = dht_sensor.readTemperature();
        humi = dht_sensor.readHumidity();
        pres = random(0, 100);
        altitude = random(0, 100);
        longitude = random(100, 5000);
        epochTime = getTime();

        appendToGSheet(temp, humi, pres, altitude, longitude, epochTime);
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


// #include "main.h"

// // Timer variables
// unsigned long lastTime = 0;
// unsigned long timerDelay = 10000;
// unsigned long sendDataPrevMillis = 0;
// bool signupOK = false;
// int count = 0;

// // Firebase objects
// FirebaseData fbdo;
// FirebaseAuth auth;
// FirebaseConfig config;
// WebServer server(80);

// // DHT sensor
// DHT dht_sensor(Dht_Sensor_Pin, Dht_type);

// void setup()
// {
//   Serial.begin(115200);
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   // pinMode(WifiConnectedLed, OUTPUT);
//   //  setup_googlesheet();

//   if (!LittleFS.begin(true))
//   {
//     Serial.print("error occure while littleFs monuting ");
//     return;
//   }

//   File file = LittleFS.open("/data.txt");

//   if (!file)
//   {
//     Serial.print("can't open the file");
//   }

//   Serial.print("file content are:");
//   while (file.available())
//   {
//     Serial.write(file.read());
//   }

//   Serial.print("readed and closed");
//   file.close();

//   WiFi_setup();

//   /* Assign the api key (required) */
//   config.api_key = API_KEY;

//   /* Assign the RTDB URL (required) */
//   config.database_url = DATABASE_URL;

//   /* Sign up */
//   if (Firebase.signUp(&config, &auth, "", ""))
//   {
//     Serial.println("ok");
//     signupOK = true;
//   }
//   else
//   {
//     Serial.printf("%s\n", config.signer.signupError.message.c_str());
//   }

//   /* Assign the callback function for the long running token generation task */
//   config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

//   Firebase.begin(&config, &auth);
//   //Firebase.reconnectWiFi(true);
// }


// void WiFi_setup()
// {
//  while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.println();

//   Serial.print("Connected with IP: ");
//   Serial.println(WiFi.localIP());
//   Serial.println();
//   digitalWrite(WifiConnectedLed, HIGH);

// }

// void temperature_humidity_firebase(float Temperature, float Humidity)
// {
//   // Write an Float number on the database path test/float
//   if (Firebase.RTDB.setFloat(&fbdo, "dht/humidity", Humidity))
//   {

//     Serial.print("\nHumidity:  ");
//     Serial.println(Humidity);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());
//     Serial.print("  TYPE: ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("\nREASON: ");
//     Serial.print(fbdo.errorReason());
//   }

//   // Write an Int number on the database path test/int
//   if (Firebase.RTDB.setInt(&fbdo, "dht/temperature", Temperature))
//   {

//     Serial.print("\nTemperature:  ");
//     Serial.println(Temperature);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());

//     Serial.print("\nTYPE:  ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("REASON: ");
//     Serial.print(fbdo.errorReason());
//   }
// }

// void current_voltage_capacity_to_firebase()
// {
//   if (Firebase.RTDB.setFloat(&fbdo, "battery/capacity", capacity))
//   {

//     Serial.print("\nCapacity:  ");
//     Serial.println(capacity);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());
//     Serial.print("  TYPE: ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("\nREASON: ");
//     Serial.print(fbdo.errorReason());
//   }

//   if (Firebase.RTDB.setFloat(&fbdo, "battery/current", current))
//   {

//     Serial.print("\nRnadom Current:  ");
//     Serial.println(current);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());
//     Serial.print("  TYPE: ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("\nREASON: ");
//     Serial.print(fbdo.errorReason());
//   }

//   if (Firebase.RTDB.setFloat(&fbdo, "battery/voltage", voltage))
//   {

//     Serial.print("\nRandom Voltage:  ");
//     Serial.println(current);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());
//     Serial.print(" TYPE: ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("\nREASON: ");
//     Serial.print(fbdo.errorReason());
//   }

//   if (Firebase.RTDB.setFloat(&fbdo, "battery/kmrange", Kmrange))
//   {

//     Serial.print("\nRandom Range:  ");
//     Serial.println(current);
//     Serial.println("\nPASSED to firebase");
//     Serial.print("\nPATH: ");
//     Serial.print(fbdo.dataPath());
//     Serial.print(" TYPE: ");
//     Serial.print(fbdo.dataType());
//   }
//   else
//   {
//     Serial.println("\nFAILED");
//     Serial.print("\nREASON: ");
//     Serial.print(fbdo.errorReason());
//   }
// }

// void check_button()
// {
//     if (!digitalRead(switch_pin))
//   {
//     led_status = !led_status;
//     Serial.print("button is pressed to change led status ");
//     Serial.print(led_status);
//   }
// }

// void loop()
// {

//   check_button();
//   // loop_googlesheet();

//   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0))
//   {
//     sendDataPrevMillis = millis();

//     Humi = dht_sensor.readTemperature();
//     Temp = dht_sensor.readHumidity();
//     digitalWrite(DataSendedLed, HIGH);

//     temperature_humidity_firebase(Temp, Humi);
//     current_voltage_capacity_to_firebase();

//     if (Firebase.RTDB.getBool(&fbdo, "switch/led_status"))
//     {
//       led_status = fbdo.boolData();
//       digitalWrite(database_led, led_status);
//     }
//     else
//     {
//       Serial.print("switch is not getted");
//     }
//   }
// }
