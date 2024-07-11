#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "Raymond";
const char* password = "lithiumRanger";
long lastOTATime = millis();

WiFiServer server(23);
WiFiClient remoteClient;

void setup() {
  Serial.begin(115200);

  // Wifi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  server.begin();
  Serial.println("Server started");
  Serial.println("IP Address: " + WiFi.localIP());

  // OTA setup
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else
      type = "filesystem";

    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
}

void loop() {
  if (server.hasClient()) {
    if (remoteClient.connected()) {
      Serial.println("Connection rejected: already connected");
      server.available().stop();
    } else {
      Serial.println("Connection accepted");
      remoteClient = server.available();
    }
  }

  if (remoteClient.connected()) {
    remoteClient.println("Hello World! This is ESP32");
    delay(1000);
  }

  // OTA check
  if (millis() - lastOTATime > 1000) {
    ArduinoOTA.handle();
    lastOTATime = millis();
  }
}
