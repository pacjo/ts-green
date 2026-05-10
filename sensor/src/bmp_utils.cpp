#include "DFRobot_BMP280.h"
#include "bmp_utils.h"
#include "Wire.h"

typedef DFRobot_BMP280_IIC BMP280;

BMP280 bmp(&Wire, BMP280::eSdoLow);

void setupBmp() {
  bmp.reset();
  bmp.begin();
}

PressureReading* takePressure() {
    float pressure_raw = bmp.getPressure();
    float pressure = pressure_raw / 100.0f;

    return new PressureReading(pressure);
}
