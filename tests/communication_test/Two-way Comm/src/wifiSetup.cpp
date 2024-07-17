#include <wifiSetup.h>


namespace wifiSetup {

    uint8_t* broadcastAddress = const_cast<uint8_t*>(slave_address);
    uint8_t* currentAddress = const_cast<uint8_t*>(master_address);

    bool success;

    int outgoing_Opcode;

    struct_message incomingReadings;

    int incomingOpcode;

    esp_now_peer_info_t peerInfo;

    
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

        if (len == sizeof(Message)) {
        Message incomingMessage;
        memcpy(&incomingMessage, incomingData, sizeof(Message));

        Serial.print("Opcode: ");
        Serial.println(static_cast<uint8_t>(incomingMessage.opcode), HEX);
        // Handle the received message
        } else {
            Serial.println("Received data size mismatch");
        }
    }

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
        Serial.print("\r\nLast Packet Send Status:\t");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

        if (status ==0){
            success = true;
        }
        else{
            success = false;
        }
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

    void sendMessage(const Message& message) {
        uint8_t data[sizeof(Message)];
        memcpy(data, &message, sizeof(Message));

        esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));
        if (result == ESP_OK) {
            Serial.println("Sent with success");
        } else {
            Serial.println("Error sending the data");
        }
}

    void setupWifi(){
        WiFi.mode(WIFI_STA);
        WiFi.begin();

        if (esp_now_init() != ESP_OK) {
            Serial.println("Error initializing ESP-NOW");
            return;
        }
        esp_now_register_send_cb(OnDataSent);
        esp_now_register_recv_cb(OnDataRecv);
        memcpy(peerInfo.peer_addr, broadcastAddress, 6);
        peerInfo.channel = 0;  
        peerInfo.encrypt = false;

        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            Serial.println("Failed to add peer");
            return;
        } else {
            Serial.println("Successfully added peer");
        }
    }


    
    /*
    Example of sending data
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoing_Opcode, sizeof(outgoing_Opcode));
   
    if (result == ESP_OK) {
        Serial.println("Sent with success");
    }
     else {
        Serial.println("Error sending the data");
    }
    */
    

}