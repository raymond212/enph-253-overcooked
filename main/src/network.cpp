#include <network.h>

namespace Network {
  String message;

  WiFiServer server(WIFI_PORT);
  WiFiClient remoteClient;

  void setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      delay(1000);
      ESP.restart();
      Serial.println("Could not connect");
    }

    server.begin();
    Serial.println("Server started");
    Serial.println("IP Address: " + WiFi.localIP());
  }

  void wifiPrintln(String msg) {
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
      remoteClient.println(msg);
    }
  }

  bool wifiInput() {
    if (server.hasClient()) {
      if (remoteClient.connected()) {
        Serial.println("Connection rejected: already connected");
        server.available().stop();
      } else {
        Serial.println("Connection accepted");
        remoteClient = server.available();
      }
    }
    if (remoteClient.connected() && remoteClient.available()) {
      message = remoteClient.readStringUntil('\n');
      message.trim();
      if (message.length() > 0) {
        Serial.println("Received: " + message);
        wifiPrintln("Received:" + message);
        return true;
      }
    }
    return false;
  }
}