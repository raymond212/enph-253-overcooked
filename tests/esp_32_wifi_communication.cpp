#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

//Master ID: d4:8a:fc:a8:57:28
//Slave ID:  d4:8a:fc:a8:4d:8c


//Master code:

//uint8_t masterAddress[] = {0xD4, 0x8A, 0xFC, 0xA8, 0x4D, 0x8C};
//uint8_t slaveAddress[] = {0xD4, 0x8A, 0xFC, 0xA8, 0x57, 0x28};

uint8_t broadcastAddress[] = {0xD4, 0x8A, 0xFC, 0xA8, 0x4D, 0x8C};

bool success;

const int ledPin = 2;



esp_now_peer_info_t peerInfo;
// Callback when data is sent

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = true;
    digitalWrite(ledPin, 1);
  }
  else{
    success = false;
    digitalWrite(ledPin, 0);
  }
}

typedef struct struct_message {
    int opcode;
} struct_message;

int outgoing_Opcode = 2;

struct_message incomingReadings;

int incomingOpcode;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
    incomingOpcode = incomingReadings.opcode;
    Serial.println("Incoming opcode: ");
    Serial.println(incomingOpcode);
}

void readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial.println("Failed to read MAC address");
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    digitalWrite(ledPin, 0);
    return;
  } else {
    digitalWrite(ledPin, 1);
  }

  esp_now_register_recv_cb(OnDataRecv);

}
 
void loop(){
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoing_Opcode, sizeof(outgoing_Opcode));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(1000);
}
