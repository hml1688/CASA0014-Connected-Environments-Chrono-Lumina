#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Keypad.h>
#include <utility/wifi_drv.h>
#include "secret.h"

// WiFi and MQTT settings
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqtt_username = SECRET_MQTTUSER;
const char* mqtt_password = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1884;
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//red blink
bool isBlinking = false;
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 1000; // flicker interval (milliseconds)

// Global variables
bool inMoistureCheckMode = false;  // Whether the soil moisture is detected
unsigned long lastSoilCheckTime = 0; // Time of last soil moisture test
const unsigned long soilCheckInterval = 1000; // The interval between each test (milliseconds)
bool isGreenBlinking = false; // Whether the light flashes green

WiFiServer server(80);
WiFiClient mkrClient;
PubSubClient client(mkrClient);

// MQTT topics
char mqtt_topic_demo[] = "student/CASA0014/light/27/brightness/";
char mqtt_topic_pixel[] = "student/CASA0014/light/27/pixel/";

// Keypad settings
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Soil moisture sensor
const int soilMoisturePin = A0;

// Global variables
unsigned long cycleStartTime;
int selectedCycle = 0;
bool inCycleSelectionMode = false;
bool inCountdownMode = false;
unsigned long selectionStartTime;
int yellowPixels = 0; // Count of yellow pixels
int cycleTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.setHostname("Lumina ucfnaoa");
  startWifi();
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("Setup complete");

// Set Neopixel brightness
  char mqtt_message[50];
  sprintf(mqtt_message, "{\"brightness\": 119}"); // Set brightness to maximum
  client.publish(mqtt_topic_demo, mqtt_message);
  Serial.println("Brightness message published");

}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }

  if (WiFi.status() != WL_CONNECTED){
    startWifi();
  }

  client.loop();

  char key = keypad.getKey();
  if (key) {
    handleKeypadInput(key);
    selectionStartTime = millis(); // Reset the timer on each key press
  }

  if (inCycleSelectionMode && millis() - selectionStartTime > 10000) {
    resetToInitialMode();
  }

  if (inCountdownMode) {
    handleCountdown();
  }

  if (isBlinking) {
    handleBlinking();
  }
  if (inMoistureCheckMode) {
    handleSoilMoistureCheck();
  }

}

void handleKeypadInput(char key) {
  if (key == '0') {
    resetToInitialMode();
    return;
  }
  if (!inCycleSelectionMode && !inCountdownMode) {
    if (key == '*') {
      enterCycleSelectionMode();
    }
  }
  if (key == '1' && isBlinking) { // Press "1" when flashing red
      Serial.println("Entering soil moisture check mode.");
      inMoistureCheckMode = true;
      isBlinking = false; // Stop flashing red light
  }

  if (key == '1' && isGreenBlinking) { // Press "1" when flashing green
      // Exit the humidity detection mode and restart the countdown period
      Serial.println("Exiting moisture check mode, resuming countdown.");
      inMoistureCheckMode = false;
      isGreenBlinking = false;
      inCountdownMode = true;
      //cycleStartTime = millis();
      cycleStartTime = millis() - (millis() % (selectedCycle * 1000));
    for (int i = 0; i < 12; i++) {
      publishNeopixelState(i, 0, 255, 0); // Green
    }

  }
  
   else if (inCycleSelectionMode) {
    if (key == 'A' || key == 'B' || key == 'C') {
      selectCycle(key);
    } else if (key == '#') {
      confirmCycle();
    }
  }
}

void enterCycleSelectionMode() {
  Serial.println("Entering cycle selection mode");
  inCycleSelectionMode = true;
  selectionStartTime = millis();
  for (int i = 0; i < 12; i++) {
    publishNeopixelState(i, 255, 255, 0); // Yellow
  }
}

void selectCycle(char key) {
  Serial.println("Cycle selected");
  //int cycleTime = 0;
  if (key == 'A') {
    cycleTime = 1 * 60; // 7 minutes, test mode: 1 minute
    for (int i = 0; i < 12; i++) {
      publishNeopixelState(i, 255, 192, 203); // Pink
    }
  } else if (key == 'B') {
    cycleTime = 15 * 60; // 15 minutes
    for (int i = 0; i < 12; i++) {
      publishNeopixelState(i, 255, 255, 255); // White
    }
  } else if (key == 'C') {
    cycleTime = 30 * 60; // 30 minutes
    for (int i = 0; i < 12; i++) {
      publishNeopixelState(i, 255, 165, 0); // Orange
    }
  }
  selectedCycle = cycleTime;
}

void confirmCycle() {
  Serial.println("Cycle confirmed");
  inCycleSelectionMode = false;
  inCountdownMode = true;
  cycleStartTime = millis();
  yellowPixels = 0; // Reset yellow pixel count
  for (int i = 0; i < 12; i++) {
    publishNeopixelState(i, 0, 255, 0); // Green
  }
}

void handleCountdown() {
  unsigned long elapsed = millis() - cycleStartTime;
  if (elapsed > selectedCycle * 1000) {
    inCountdownMode = false;
    isBlinking = true; // start flashing red light
    Serial.println("Countdown complete");
    }
/*    int soilMoistureValue = analogRead(soilMoisturePin);
    if (soilMoistureValue > 600) { // Adjust threshold as needed
      Serial.println("Soil moisture low, needs watering, Moisture value: ");
      Serial.println(soilMoistureValue);
    } else {
      Serial.print("Soil moisture sufficient, Moisture value: ");
      Serial.println(soilMoistureValue);
    }
  }*/ 
  else {
    int interval = selectedCycle * 1000 / 12;
    if (elapsed % interval == 0 && yellowPixels < 12) {
      publishNeopixelState(yellowPixels, 255, 255, 0); // Yellow
      yellowPixels++;
      Serial.print("Countdown time left: ");
      Serial.print(selectedCycle - (elapsed / 1000));
      Serial.println(" seconds");
      Serial.print("Yellow pixels: ");
      Serial.print(yellowPixels);
      Serial.print(", Green pixels: ");
      Serial.println(12 - yellowPixels);
    }
  }
}

void resetToInitialMode() {
  Serial.println("Resetting to initial mode");
  inCycleSelectionMode = false;
  inCountdownMode = false;
  yellowPixels = 0; // Reset yellow pixel count
  isBlinking = false; // Stop flashing
  isGreenBlinking = false;
  inMoistureCheckMode = false; // exit the humidity test mode

  for (int i = 0; i < 12; i++) {
    publishNeopixelState(i, 0, 0, 255); // Blue
  }

}

void publishNeopixelState(int pixelId, int r, int g, int b) {
  char message[100];
  sprintf(message, "{\"pixelid\": %d, \"R\": %d, \"G\": %d, \"B\": %d}", pixelId, r, g, b);
  if (client.publish(mqtt_topic_pixel, message)) {
    Serial.println("Neopixel message published");
  } else {
    Serial.println("Failed to publish Neopixel message");
  }
}


void handleBlinking() {
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime > blinkInterval) {
    lastBlinkTime = currentTime;
    static bool isRed = false;
    for (int i = 0; i < 12; i++) {
      if (isRed) {
        publishNeopixelState(i, 0, 0, 0); // turn off lights
      } else {
        publishNeopixelState(i, 255, 0, 0); // turn on red lights
      }
    }
    isRed = !isRed;
  }
}

void handleSoilMoistureCheck() {
  unsigned long currentTime = millis();
  if (currentTime - lastSoilCheckTime >= soilCheckInterval) {
    lastSoilCheckTime = currentTime;
    int soilMoistureValue = analogRead(soilMoisturePin);
    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureValue);

    if (soilMoistureValue < 600) {
      // If the soil is moist enough, flash a green light
      Serial.println("Enough Water! Flashing green lights.");
      isBlinking = false; // stop flashing red lights
      isGreenBlinking = true; // flashing green lights
      blinkGreenLights();

    } else {
      // If the soil is too dry and not watered enough, flash red lights
      Serial.println("Soil moisture is not sufficient.");
      isGreenBlinking = false;
      isBlinking = true; // flashing red lights
    }
  }
}

void blinkGreenLights() {
  static unsigned long lastBlinkTime = 0;
  static bool lightsOn = false;
  unsigned long currentTime = millis();

  if (currentTime - lastBlinkTime > blinkInterval) {
    lastBlinkTime = currentTime;
    lightsOn = !lightsOn;

    for (int i = 0; i < 12; i++) {
      if (lightsOn) {
        publishNeopixelState(i, 0, 255, 0); 
      } else {
        publishNeopixelState(i, 0, 0, 0); 
      }
    }
  }
}

void startWifi(){
    
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Function for connecting to a WiFi network
  // is looking for UCL_IoT and a back up network (usually a home one!)
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    // loop through all the networks and if you find UCL_IoT or the backup - ssid1
    // then connect to wifi
    Serial.print("Trying to connect to: ");
    Serial.println(ssid);
    for (int i = 0; i < n; ++i){
      String availablessid = WiFi.SSID(i);
      // Primary network
      if (availablessid.equals(ssid)) {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
          delay(600);
          Serial.print(".");
        }
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("Connected to " + String(ssid));
          break; // Exit the loop if connected
        } else {
          Serial.println("Failed to connect to " + String(ssid));
        }
      } else {
        Serial.print(availablessid);
        Serial.println(" - this network is not in my list");
      }

    }
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void reconnectMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    startWifi();
  }
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "LuminaSelector";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}