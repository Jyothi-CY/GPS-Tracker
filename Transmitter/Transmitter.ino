#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);  // Use Serial2 for GPS

void setup() {
  Serial.begin(115200);
  Serial.println("Starting GPS and LoRa setup...");

  // Initialize GPS Serial
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS connected to GPIO16, GPIO17
  Serial.println("GPS Serial started on GPIO16 and GPIO17");

  // Initialize LoRa on 433E6 or 915E6 based on module frequency
  LoRa.setPins(5, 14, 26);  // NSS, RESET, DIO0
  Serial.println("Setting up LoRa module...");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed! Check connections.");
    while (1);
  }
  Serial.println("LoRa module started successfully at 433 MHz");
}

void loop() {
  if (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    Serial.write(c);  // Print raw GPS character to Serial Monitor
    
    // Feed each character to TinyGPS++
    if (gps.encode(c)) {
      if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println("GPS location data is invalid.");
      }
    }
  } else {
    Serial.println("No data available from GPS serial");
    delay(1000);
  }
}