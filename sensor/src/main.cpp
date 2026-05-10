#include <Arduino.h>
#include "DHT.h"
#include "led_utils.h"
#include "dht_utils.h"
#include "networking/wifi_utils.h"
#include "photodiode_utils.h"
#include "soil_utils.h"
#include "eink_utils.h"
#include "bmp_utils.h"

// sensors - TODO: move to *_utils.h
DhtTask dhtTask(5, DHT22, 500);
PhotodiodeTask photoTask(6, 500);
SoilMoistureTask soilTask(2, 500);
BmpTask bmpTask(0x76, 500);

// outputs
BlinkLedBuiltinTask blinkTask(100);
ColorWheelRgbTask rgbTask(5);
EinkTask einkTask(500);

void setup() {
    Serial.begin(115200);
    delay(1000);

    // prepare sensor queue
    setupSensorQueue();

    int sensor_priority = 10;
    xTaskCreate(SensorTask::runTask, "dht",   2048, &dhtTask,    sensor_priority, NULL);
    xTaskCreate(SensorTask::runTask, "photo", 1024, &photoTask,  sensor_priority, NULL);
    xTaskCreate(SensorTask::runTask, "soil", 1024, &soilTask,  sensor_priority, NULL);
    xTaskCreate(SensorTask::runTask, "bmp",   2048, &bmpTask,    sensor_priority, NULL);

    int output_priority = 10;
    xTaskCreate(PeriodicTask::runTask, "blink",  1024, &blinkTask, output_priority, NULL);
    xTaskCreate(PeriodicTask::runTask, "rgb",    1024, &rgbTask,   output_priority, NULL);
    xTaskCreate(PeriodicTask::runTask, "eink",   4096, &einkTask,  output_priority, NULL);

    int network_priority = 10;
    xTaskCreate(sendToNetworkTask, "sendToNetwork", 4096, NULL, network_priority, NULL);
}

void loop() { }
