#pragma once

#include "data/sensor_task.h"

class BmpTask : public SensorTask {
public:
    BmpTask(uint8_t i2cAddr = 0x76, unsigned long intervalMs = 500, const char* label = "");

    void setup() override;
    std::vector<SensorReading*> measure() override;

private:
    uint8_t i2cAddr;
    void*  bmp;   // opaque ::DFRobot_BMP280_IIC*
};
