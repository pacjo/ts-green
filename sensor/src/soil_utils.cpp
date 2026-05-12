#include <Arduino.h>
#include "soil_utils.h"

SoilMoistureTask::SoilMoistureTask(int pin, unsigned long intervalMs, int rawDry, int rawWet, const char* label)
    : SensorTask(intervalMs, label), pin(pin), rawDry(rawDry), rawWet(rawWet) {}

void SoilMoistureTask::setup() {
    pinMode(pin, INPUT);
}

std::vector<SensorReading*> SoilMoistureTask::measure() {
    float value = (analogRead(pin) - rawWet) / static_cast<float>(rawDry - rawWet);
    return { new SoilMoistureReading(value) };
}
