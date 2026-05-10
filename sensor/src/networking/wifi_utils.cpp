#include <WiFi.h>
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

    WiFiClient client;

    while (true) {
        if (!client.connected()) {
            client.stop();
            LOG_INFO("net", "connecting to %s:%d", serverIp.toString().c_str(), serverPort);

            if (!client.connect(serverIp, serverPort)) {
                LOG_WARN("net", "connect failed, retrying in 1s");
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            LOG_INFO("net", "connected to server");
        }

        SensorReading* reading = nullptr;

        // skip empty queue
        if (xQueueReceive(sensorQueue, &reading, pdMS_TO_TICKS(100)) != pdTRUE)
            continue;

        char buf[128];
        reading->toJson(buf, sizeof(buf));
        client.println(buf);

        LOG_DEBUG("net", "sent: %s  (queue: %d)", buf, uxQueueMessagesWaiting(sensorQueue));

        delete reading;
    }
}
