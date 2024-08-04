#include <wifiSetup.h>


#define TCRT_PIN 35






//Master ID: d4:8a:fc:a8:57:28
//Slave ID:  d4:8a:fc:a8:4d:8c


//Master code:

//uint8_t masterAddress[] = {0xD4, 0x8A, 0xFC, 0xA8, 0x4D, 0x8C};
//uint8_t slaveAddress[] = {0xD4, 0x8A, 0xFC, 0xA8, 0x57, 0x28};

//Need to find the MAC addresses of PICOs used

/*
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
*/

void setup(){
  Serial.begin(9600);
  wifiSetup::setupWifi();
  //pinMode(TCRT_PIN, INPUT);
}
 
void loop(){
  Message message;
  message.opcode = Opcodes::opcodes::T_BUNS;
  memset(message.data, 0, sizeof(message.data));
  esp_err_t result = wifiSetup::sendMessage(message);

  //Serial.println(result);
  delay(600);
  
}
