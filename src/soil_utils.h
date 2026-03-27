#pragma once

#define SOIL_PIN 2

/*
 * Shorthand for pinMode(SOIL_PIN, INPUT)
 */
void setupSoilMoisture();

float readSoilMoisture();
