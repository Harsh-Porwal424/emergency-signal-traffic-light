#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
//replace your Wi-Fi credentials here
const char* ssid = "";
const char* password = "";

// MQTT details
const char* mqttServer = "0.tcp.in.ngrok.io";   // Replace with Ngrok address
const int mqttPort = xxxxx;                     // Replace with Ngrok port
const char* mqttTopic = "traffic/emergency";

WiFiClient espClient;
PubSubClient client(espClient);

// Pin definitions
const int green0 = D0; // Green for pole 1
const int red1 = D1;   // Red for pole 1
const int green2 = D2; // Green for pole 2
const int red3 = D3;   // Red for pole 2
const int green4 = D4; // Green for pole 3
const int red5 = D5;   // Red for pole 3
const int green6 = D6; // Green for pole 4
const int red7 = D7;   // Red for pole 4

// Timing variables
unsigned long previousMillis = 0; // Stores the last time the lights were updated
const unsigned long greenLightDuration = 10000; // 10 seconds for emergency
bool isEmergency = false; // Flag to track emergency state
int emergencyPole = -1;   // Indicates which pole is in emergency

// Function to set the lights for a pole
void setLights(int greenPin, int redPin, bool emergency) {
  unsigned long currentMillis = millis();
  
  if (emergency) {
    if (currentMillis - previousMillis < greenLightDuration) {
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
    } else {
      // End emergency state
      isEmergency = false;
      emergencyPole = -1;
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
    }
  } else {
    // Default behavior (Red light ON, Green light OFF)
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
  }
}

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  // Handle emergency messages
  if (message == "1") {
    isEmergency = true;
    emergencyPole = 1;
    previousMillis = millis();
  } else if (message == "2") {
    isEmergency = true;
    emergencyPole = 2;
    previousMillis = millis();
  } else if (message == "3") {
    isEmergency = true;
    emergencyPole = 3;
    previousMillis = millis();
  } else if (message == "4") {
    isEmergency = true;
    emergencyPole = 4;
    previousMillis = millis();
  }
}

void setup() {
  Serial.begin(115200);

  // Set all pins as outputs
  pinMode(green0, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(green4, OUTPUT);
  pinMode(red5, OUTPUT);
  pinMode(green6, OUTPUT);
  pinMode(red7, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed. State: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Subscribe to topic
  client.subscribe(mqttTopic);
}

void loop() {
  // Ensure MQTT communication
  client.loop();

  if (isEmergency) {
    // Handle emergency lights based on the emergencyPole
    if (emergencyPole == 1) {
      setLights(green0, red1, true);
      setLights(green2, red3, false);
      setLights(green4, red5, false);
      setLights(green6, red7, false);
    } else if (emergencyPole == 2) {
      setLights(green0,red1,false);
      setLights(green2, red3, true);
      setLights(green4,red5,false);
      setLights(green6,red7,false);
    } else if (emergencyPole == 3) {
      setLights(green0, red1, false);
      setLights(green2, red3, false);
      setLights(green4, red5, true);
      setLights(green6, red7, false);
    } else if (emergencyPole == 4) {
      setLights(green0, red1, false);
      setLights(green2, red3, false);
      setLights(green4, red5, false);
      setLights(green6, red7, true);
    }
  } else {
    // Normal traffic light sequence (default behavior)
    digitalWrite(green0, HIGH);
    digitalWrite(red1, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green4, LOW);
    digitalWrite(red5, HIGH);
    digitalWrite(green6, LOW);
    digitalWrite(red7, HIGH);
    delay(2000);

    digitalWrite(green0, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(red3, LOW);
    digitalWrite(green4, LOW);
    digitalWrite(red5, HIGH);
    digitalWrite(green6, LOW);
    digitalWrite(red7, HIGH);
    delay(2000);

    digitalWrite(green0, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green4, HIGH);
    digitalWrite(red5, LOW);
    digitalWrite(green6, LOW);
    digitalWrite(red7, HIGH);
    delay(2000);

    digitalWrite(green0, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green4, LOW);
    digitalWrite(red5, HIGH);
    digitalWrite(green6, HIGH);
    digitalWrite(red7, LOW);
    delay(2000);
  }
}
