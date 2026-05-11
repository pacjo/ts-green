#include <Arduino.h>
#include "photodiode_utils.h"

// by experimentation - TODO: determine actual values
int LIGHT_MIN = 0;
int LIGHT_MAX = 4095;

PhotodiodeTask::PhotodiodeTask(int pin, unsigned long intervalMs, const char* label)
    : SensorTask(intervalMs, label), pin(pin) {}

void PhotodiodeTask::setup() {
    pinMode(pin, INPUT);
}

std::vector<SensorReading*> PhotodiodeTask::measure() {
    float value = analogRead(pin) / 4095.0f;
    return { new LightReading(value) };
}
