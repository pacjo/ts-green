#include <Arduino.h>
#include "soil_utils.h"

// by experimentation
int MOISTURE_MIN = 2800;
int MOISTURE_MAX = 1400;

SoilMoistureTask::SoilMoistureTask(int pin, unsigned long intervalMs, int rawDry, int rawWet, const char* label)
    : SensorTask(intervalMs, label), pin(pin), rawDry(rawDry), rawWet(rawWet) {}

void SoilMoistureTask::setup() {
    pinMode(pin, INPUT);
}

std::vector<SensorReading*> SoilMoistureTask::measure() {
    float value = (rawWet - analogRead(pin)) / static_cast<float>(rawWet);
    return { new SoilMoistureReading(value) };
}
