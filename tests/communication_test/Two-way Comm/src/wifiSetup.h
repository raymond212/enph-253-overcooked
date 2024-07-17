#pragma once
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <constants.h>
#include <message.h>


namespace wifiSetup {

    extern uint8_t* broadcastAddress;
    extern uint8_t* currentAddress;

    

    extern bool success;

    void sendMessage(const Message& message);

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

    typedef struct struct_message {
        int opcode;
    } struct_message;

    extern int outgoing_Opcode;

    extern struct_message incomingReadings;

    extern int incomingOpcode;

    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

    void readMacAddress();

    void setupWifi();

    extern esp_now_peer_info_t peerInfo;

}