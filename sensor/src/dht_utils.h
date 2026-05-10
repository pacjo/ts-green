#pragma once

#include "data/sensor_task.h"

#define DHT_PIN 5
#define DHT_TYPE DHT22

class DhtTask : public SensorTask {
public:
    DhtTask(int pin, int dhtType = 22, unsigned long intervalMs = 500, const char* label = "");

    void setup() override;
    SensorReading* measure() override;

private:
    int    pin;
    int    dhtType;
    void*  dht;   // opaque ::DHT*
};
