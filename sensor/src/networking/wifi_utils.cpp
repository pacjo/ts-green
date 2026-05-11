#include <WiFi.h>
#include <WiFiUdp.h>
#include "wifi_utils.h"
#include "data/sensor_reading.h"
#include "logger.h"

// TODO: change below
const char* ssid = "";
const char* password = "";

// TODO: change below
const IPAddress serverIp(10,207,185,1);
const int serverPort = 6000;

void connectToWifi() {
    LOG_INFO("wifi", "connecting to %s ...", ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(500));
        LOG_DEBUG("wifi", "waiting for connection...");
    }

    LOG_INFO("wifi", "connected, IP: %s", WiFi.localIP().toString().c_str());
}

void sendToNetworkTask(void* pvParameters) {
    connectToWifi();

    WiFiUDP udp;

    while (true) {
        SensorReading* reading = nullptr;

        // skip empty queue
        if (xQueueReceive(sensorQueue, &reading, pdMS_TO_TICKS(100)) != pdTRUE)
            continue;

        char buf[128];
        reading->toJson(buf, sizeof(buf));

        udp.beginPacket(serverIp, serverPort);
        udp.print(buf);
        udp.endPacket();

        LOG_DEBUG("net", "sent: %s  (queue: %d)", buf, uxQueueMessagesWaiting(sensorQueue));

        delete reading;
    }
}
