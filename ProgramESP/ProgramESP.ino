#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Pins
#define DEVICE_PUMP 4
#define DEVICE_LIGHT 32
#define DEVICE_FAN 33
#define SENSOR_HUMIDITY 36
#define SENSOR_INSOLATION 39
#define SENSOR_THERMOMETER 14

const int msg_delay = 500;

//Mqtt topics configuration
const uint8_t SectionID = 1;
const char greenhousedataTopic[] = "/Greenhouse/data/";
const char pumpTopic[] = "/Section1/pump";
const char lightTopic[] = "/Section1/light";
const char fanTopic[] = "/Section1/fan";

//Network settings
const char* ssid = "......";
const char* password = "......";
const char* mqtt_server = "......."; //IP adress

struct GreenhouseData{
    uint8_t id = SectionID; 
    uint8_t temperature;
    uint8_t insolation;
    uint8_t humidity;
};

WiFiClient espClient;
PubSubClient client(espClient);
OneWire oneWire(SENSOR_THERMOMETER);
DallasTemperature thermometer(&oneWire);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  thermometer.begin();
  
  pinMode(DEVICE_PUMP, OUTPUT);
  pinMode(DEVICE_LIGHT, OUTPUT);
  pinMode(DEVICE_FAN, OUTPUT);
  digitalWrite(DEVICE_PUMP, LOW);
  digitalWrite(DEVICE_LIGHT, LOW);
  digitalWrite(DEVICE_FAN, LOW);
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  bool request = static_cast<bool>(&message);
  if (String(topic) == pumpTopic) digitalWrite(DEVICE_PUMP, request);
  if (String(topic) == lightTopic) digitalWrite(DEVICE_LIGHT, request);
  if (String(topic) == fanTopic) digitalWrite(DEVICE_FAN, request);
}

void reconnect() {
  while (!client.connected()) { 
    if (client.connect("ESP8266Client")) {
      client.subscribe(pumpTopic);
      client.subscribe(lightTopic);
      client.subscribe(fanTopic);
    } else {
      delay(5000);
    }
  }
}

GreenhouseData getGreenhouseData() {
  thermometer.requestTemperatures();
  float temperature = thermometer.getTempCByIndex(0);
  int humidity = map(analogRead(SENSOR_HUMIDITY), 0, 4095, 0, 100);
  int insolation = map(analogRead(SENSOR_INSOLATION), 0, 4095, 0, 100);

  GreenhouseData data;
  data.temperature = static_cast<uint8_t>(temperature);
  data.humidity = static_cast<uint8_t>(humidity);
  data.insolation = static_cast<uint8_t>(insolation);
  return data;
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  GreenhouseData data = getGreenhouseData();
  byte *data_ptr = (byte*)malloc(sizeof(GreenhouseData));
  memcpy(data_ptr, reinterpret_cast<byte*>(&data), sizeof(GreenhouseData));
  client.publish(greenhousedataTopic, data_ptr, sizeof(GreenhouseData));
  delay(msg_delay); 
}
