#include <WiFi.h>
#include "wifi_utils.h"
#include "data/sensor_reading.h"

// TODO: change below
const char* ssid = "";
const char* password = "";

// TODO: change below
const IPAddress serverIp(10,207,185,1);
const int serverPort = 6000;

void connectToWifi() {
    Serial.print("Connecting to WiFi...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    Serial.println("\tconnected!");
    Serial.println(WiFi.localIP());
}

void sendToNetworkTask(void* pvParameters) {
    connectToWifi();

    WiFiClient client;
    client.connect(serverIp, serverPort);

    while (true) {
        SensorReading* reading = nullptr;

        // skip empty queue
        if (xQueueReceive(sensorQueue, &reading, pdMS_TO_TICKS(100)) != pdTRUE)
            continue;

        // TODO: handle client not connected

        char buf[128];
        reading->toJson(buf, sizeof(buf));
        client.println(buf);
        delete reading;
    }
}
