#include <Arduino.h>
#include "soil_utils.h"

// by experimentation
int MOISTURE_MIN = 2800;
int MOISTURE_MAX = 1400;

void setupSoilMoisture() {
    pinMode(SOIL_PIN, INPUT);
}

float readSoilMoisture() {
    return (MOISTURE_MAX - analogRead(SOIL_PIN)) / (float) MOISTURE_MAX;
}

SoilMoistureReading* takeSoilMoisture() {
    float value = readSoilMoisture();
    return new SoilMoistureReading(value);
}
