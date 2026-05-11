#pragma once

#include "periodic_task.h"
#include "data/sensor_reading.h"

/**
 * A PeriodicTask that produces one SensorReading per tick.
 */
class SensorTask : public PeriodicTask {
public:
    const char* label;

    void tick() override final {
        for (auto reading : measure()) {
            reading->label = this->label;
            pushReading(reading);
        }
    }

    virtual std::vector<SensorReading*> measure();

protected:
    explicit SensorTask(unsigned long intervalMs, const char* label = "")
        : PeriodicTask(intervalMs), label(label) {}
};
