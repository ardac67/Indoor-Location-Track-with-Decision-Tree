#include <WiFi.h>
#include <ArduinoJson.h>
int counter = 1;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("Starting WiFi scan...");
  WiFi.scanNetworks(true);
}

bool isTargetSSID(const String& ssid) {
  const char* targets[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "B1", "B2"};
  for (const char* target : targets) {
    if (ssid == target) {
      return true;
    }
  }
  return false;
}

void loop() {
  int scanStatus = WiFi.scanComplete();
  if (scanStatus == WIFI_SCAN_FAILED) {
    Serial.println("Scan failed. Restarting...");
    WiFi.scanNetworks(true);
  } else if (scanStatus >= 0) {
    Serial.println("Scan complete");
    int numNetworks = WiFi.scanComplete();
    counter++;
    
    Serial.println("Networks found: " + String(numNetworks));
    
    if (numNetworks == 0) {
      Serial.println("No targeted WiFi networks found");
    } else {
      DynamicJsonDocument doc(4096); 
      doc["__location"] = "A7";
      for (int i = 0; i < numNetworks; ++i) {
        String ssid = WiFi.SSID(i);
        if (isTargetSSID(ssid)) {
          int rssi = WiFi.RSSI(i);
          doc[ssid] = rssi;
        }
      }
      if (!doc.isNull()) {
        serializeJson(doc, Serial);
        Serial.println();
      } else {
        Serial.println("No targeted WiFi networks found.");
      }
    }
    WiFi.scanDelete();
    if (WiFi.scanComplete() == WIFI_SCAN_FAILED) {
      WiFi.scanNetworks(true);
    }
  }
  delay(3000);
}
