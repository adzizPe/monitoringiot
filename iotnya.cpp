// Contoh kode Arduino/ESP32
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHT_PIN 4
#define TRIG_PIN 5
#define ECHO_PIN 18
#define DHT_TYPE DHT21

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

void setup() {
  // Setup WiFi dan sensor
  WiFi.begin("SSID", "PASSWORD");
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Setup API endpoint
  server.on("/sensor-data", handleSensorData);
  server.begin();
}

void handleSensorData() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  float distance = readUltrasonic();
  
  String json = "{";
  json += "\"temperature\":" + String(temp) + ",";
  json += "\"humidity\":" + String(humid) + ",";
  json += "\"distance\":" + String(distance);
  json += "}";
  
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", json);
}