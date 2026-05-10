#include "DFRobot_BMP280.h"
#include "bmp_utils.h"
#include "Wire.h"

typedef DFRobot_BMP280_IIC BMP280;

BmpTask::BmpTask(uint8_t i2cAddr, unsigned long intervalMs, const char* label)
    : SensorTask(intervalMs, label), i2cAddr(i2cAddr), bmp(nullptr) {}

void BmpTask::setup() {
    bmp = new BMP280(&Wire, BMP280::eSdoLow);
    auto* sensor = static_cast<BMP280*>(bmp);
    sensor->reset();
    sensor->begin();
}

SensorReading* BmpTask::measure() {
    auto* sensor = static_cast<BMP280*>(bmp);
    float pressure = sensor->getPressure() / 100.0f;

    return new PressureReading(pressure);
}
