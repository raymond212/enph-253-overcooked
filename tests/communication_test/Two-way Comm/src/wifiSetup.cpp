#include <wifiSetup.h>


namespace wifiSetup {

    uint8_t broadcastAddress[6];
    uint8_t currentAddress[6];

    bool send;

    int incomingReadings;


    esp_now_peer_info_t peerInfo;
    
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

        if (len == sizeof(incomingReadings)) {
            memcpy(&incomingReadings, incomingData, sizeof(int));

            Serial.print("Opcode: ");
            Serial.println(incomingReadings);

        // Handle the received message
        } else {
            Serial.println("Received data size mismatch");
        }
    }

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
        Serial.print("\r\nLast Packet Send Status:\t");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        send = status == ESP_NOW_SEND_SUCCESS;
    }

    int getCurr_Opcode() {
        return incomingReadings;
    }

    void readMacAddress(){
        uint8_t baseMac[6];
        esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
        if (ret == ESP_OK) {
            memcpy(currentAddress, baseMac, 6);
            Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
        } else {
            Serial.println("Failed to read MAC address");
        }
    }

    esp_err_t sendMessage(const int& message) {
        uint8_t data[sizeof(message)];
        memcpy(data, &message, sizeof(message));        

        esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));
       
        return result;
    }


    void setupWifi(){
        WiFi.mode(WIFI_STA);



        if (esp_now_init() != ESP_OK) {
            Serial.println("Error initializing ESP-NOW");
            return;
        }
        esp_now_register_send_cb(OnDataSent);
        esp_now_register_recv_cb(OnDataRecv);
        readMacAddress();

        if (memcmp(currentAddress, top_robot_address, sizeof(top_robot_address)) == 0) {
            memcpy(broadcastAddress, bottom_robot_address, sizeof(bottom_robot_address));
        } else {
            memcpy(broadcastAddress, top_robot_address, sizeof(top_robot_address));
        }

         Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  currentAddress[0], currentAddress[1], currentAddress[2],
                  currentAddress[3], currentAddress[4], currentAddress[5]);

        Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  broadcastAddress[0], broadcastAddress[1], broadcastAddress[2],
                  broadcastAddress[3], broadcastAddress[4], broadcastAddress[5]);
    
    
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
    

}
