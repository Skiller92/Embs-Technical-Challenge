#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_MAX30100.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
#include <Firebase.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define FIREBASE_HOST "votrefirebase.firebaseio.com"
#define FIREBASE_AUTH "votreauthentificationfirebase"

#define WIFI_SSID "votressidwifi"
#define WIFI_PASSWORD "votremotdepassewifi"

#define MQTT_SERVER "votreserveurmqtt"
#define MQTT_PORT 1883
#define MQTT_USER "votreutilisateurmqtt"
#define MQTT_PASSWORD "votremotdepassemqtt"

#define DHTPIN 2  // Broche à laquelle le capteur DHT11 est connecté
#define DHTTYPE DHT11  // Type de capteur DHT

DHT dht(DHTPIN, DHTTYPE);
MQUnifiedsensor gasSensor("MQ-2", 0, 1, 2, 3, 4, 5, 6); // Nommez vos broches en fonction de votre configuration
Adafruit_MAX30100 pulseSensor;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  delay(10);

  dht.begin();
  gasSensor.begin();
  pulseSensor.begin();
  accel.begin();

  connectWiFi();
  connectMQTT();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float gasQuality = gasSensor.readValue(MQ_READ_RAW);
  int heartRate = pulseSensor.getHeartRate();
  sensors_event_t event;
  accel.getEvent(&event);
  int steps = calculateSteps(event.acceleration.x, event.acceleration.y, event.acceleration.z);

  sendToFirebase(temperature, humidity, gasQuality, heartRate, steps);

  delay(5000); // Attendre 5 secondes entre chaque envoi de données
}

int calculateSteps(float x, float y, float z) {
  // Implémentez votre logique pour calculer le nombre de pas ici
  // Utilisez les valeurs d'accélération (x, y, z) du capteur ADXL345
}

void sendToFirebase(float temperature, float humidity, float gasQuality, int heartRate, int steps) {
  if (client.connected()) {
    String data = "{";
    data += "\"temperature\":" + String(temperature) + ",";
    data += "\"humidity\":" + String(humidity) + ",";
    data += "\"gasQuality\":" + String(gasQuality) + ",";
    data += "\"heartRate\":" + String(heartRate) + ",";
    data += "\"steps\":" + String(steps);
    data += "}";

    String topic = "/arduinoData";
    client.publish(topic.c_str(), data.c_str());
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void connectMQTT() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  while (!client.connected()) {
    if (client.connect("arduinoClient", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("MQTT Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
