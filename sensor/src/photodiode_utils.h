#pragma once

#include "data/sensor_task.h"

#define PHOTODIODE_PIN 6

class PhotodiodeTask : public SensorTask {
public:
    PhotodiodeTask(int pin, unsigned long intervalMs = 500, const char* label = "");

    void setup() override;
    std::vector<SensorReading*> measure() override;

private:
    int pin;
};
