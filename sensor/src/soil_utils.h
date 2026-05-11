#pragma once

#include "data/sensor_task.h"

#define SOIL_PIN 2

class SoilMoistureTask : public SensorTask {
public:
    SoilMoistureTask(int pin, unsigned long intervalMs = 500, int rawDry = 2800, int rawWet = 1400, const char* label = "");

    void setup() override;
    std::vector<SensorReading*> measure() override;

private:
    int pin;
    int rawDry;
    int rawWet;
};
