#include <Arduino.h>
#include "soil_utils.h"

// by experimentation - TODO: determine actual values
int MOISTURE_MIN = 0;
int MOISTURE_MAX = 4095;

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