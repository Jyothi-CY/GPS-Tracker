#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "JYO";
const char* password = "Nana_9177";
const char* serverUrl = "http://your-server-ip:5000/update-location";  // Node.js server endpoint

void setup() {
  Serial.begin(9600);
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // LoRa setup
  LoRa.setPins(5, 14, 26);  // NSS, RESET, DIO0 for LoRa
  if (!LoRa.begin(433E6)) {  // Set frequency to 433 MHz (adjust as per your module)
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa receiver setup complete.");
}

void sendToServer(String gpsData) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Parse latitude and longitude from received data
    int commaIndex = gpsData.indexOf(',');
    String latitude = gpsData.substring(0, commaIndex);
    String longitude = gpsData.substring(commaIndex + 1);

    // Create JSON payload
    String jsonPayload = "{\"latitude\":" + latitude + ",\"longitude\":" + longitude + "}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(jsonPayload);
    if (httpResponseCode > 0) {
      Serial.println("Data sent to server successfully");
    } else {
      Serial.println("Error sending data to server");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read LoRa packet
    String gpsData = "";
    while (LoRa.available()) {
      gpsData += (char)LoRa.read();
    }
    Serial.println("Received GPS data: " + gpsData);

    // Send GPS data to server
    sendToServer(gpsData);
  }
}
