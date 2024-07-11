#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Raymond";
const char* password = "lithiumRanger";

WiFiServer server(23);
WiFiClient remoteClient;

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  server.begin();
  Serial.println("Server started");
  Serial.println("IP Address: " + WiFi.localIP());
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
    remoteClient.println("Hello World!");
    delay(1000);
  }
}
