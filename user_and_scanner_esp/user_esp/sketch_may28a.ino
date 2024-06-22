#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <eloquent_rtls.h>
#include <eloquent_rtls/wifi.h>
#include "FeaturesConverter.h"
#include <queue>
#include <Arduino.h>
#define EAP_IDENTITY "a.caltepe2021@gtu.edu.tr"


std::queue<String> messageQueue;

#define LED 2
TaskHandle_t PredictTaskHandle = NULL;
TaskHandle_t ClientTaskHandle = NULL;
using eloq::rtls::wifiScanner;
using eloq::rtls::FeaturesConverter;
WiFiClient client;
FeaturesConverter converter(wifiScanner, &client);

String output12State = "off";
String output14State = "off";
const int output12 = 12;
const int output14 = 14;

const char* ssid = "Superbox_Wifi_4138";  // SSID of your Wi-Fi network
const char* password = "bvftr56j.";  // Password for your Wi-Fi network
const char* host = "192.168.1.136";  // IP address of your server
const uint16_t port = 8080;  // TCP port for connection



unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

const static String id = "0";
String readBuffer = "";  

void predictTask(void *parameter) {
  for (;;) {  
    Serial.println(converter.predict());
    vTaskDelay(pdMS_TO_TICKS(2000)); 
  }
}

void clientTask(void *parameter) {
  for (;;) { 
    if (!client.connected()) {
      client.stop();
      connectToServer(); 
    }

    while (client.available()) {
      char c = client.read();
      readBuffer += c;
    }
    messageQueue.push(readBuffer);
    readBuffer ="";

    if (!messageQueue.empty()) {
      String message = messageQueue.front(); 
      messageQueue.pop(); 

      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, message);
      if (error) {
        while (!client.connect(host, port)) {
          delay(2000);
        }
      } else {
        const char* status = doc["status"];
        if (status != NULL) {
          const String to = doc["to"];
          if (to == id) {
            if (strcmp(status, "hit") == 0) {
              digitalWrite(output12, HIGH);
              delay(1000);
              digitalWrite(output12, LOW);
              delay(1000);
              digitalWrite(output12, HIGH);
              delay(1000);
              digitalWrite(output12, LOW);
            } else if (strcmp(status, "dead") == 0) {
              digitalWrite(output14, LOW);
              delay(1000);
              digitalWrite(output14, HIGH);
            } else if (strcmp(status, "revive") == 0) {
              Serial.println("BUUUUUUM");
              digitalWrite(output14, LOW);
              delay(1000);
              digitalWrite(output14, LOW);
            }
          }
          if (strcmp(status, "game_end") == 0) {
            digitalWrite(output12, HIGH);
            digitalWrite(output14, HIGH);
          }
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(100)); 
  }
}

void setup() {
  delay(3000);
  Serial.begin(115200);
  pinMode(output12, OUTPUT);
  pinMode(output14, OUTPUT);

  
  digitalWrite(output12, LOW);
  digitalWrite(output14, LOW);
  Serial.println("__RTLS WIFI__");
  
  wifiScanner.identifyBySSID();
  wifiScanner.discardWeakerThan(-120);

  converter.verbose();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  connectToServer();

  xTaskCreatePinnedToCore(
    predictTask,          
    "PredictTask",      
    10000,                
    NULL,                 
    1,                   
    &PredictTaskHandle,   
    0); 

  xTaskCreatePinnedToCore(
    clientTask,          
    "ClientTask",        
    10000,                
    NULL,                 
    1,                    
    &ClientTaskHandle,   
    1); 
}

void loop() {}

void connectToServer() {
  while (!client.connect(host, port)) {
    Serial.println("Connection to server failed. Retry in 5 seconds");
    delay(2000);
  }
  Serial.println("Connected to server successfully");
}
