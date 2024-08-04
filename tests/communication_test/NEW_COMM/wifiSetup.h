#pragma once
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <constants.h>
#include <message.h>
#include <esp_pm.h>


namespace wifiSetup {

    extern uint8_t broadcastAddress[6];
    extern uint8_t currentAddress[6];


    extern bool send;

    esp_err_t sendMessage(const Message& message);

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);


    extern Message incomingReadings; 

    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

    void readMacAddress();

    void setupWifi();

    extern esp_now_peer_info_t peerInfo;


    esp_err_t sendMessageTimes(const Message& message, int attempts);


    Opcodes::opcodes getCurr_Opcode();

}
