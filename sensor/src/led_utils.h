#pragma once

#include "data/periodic_task.h"

#define LED_R 14
#define LED_G 8
#define LED_B 17

class BlinkLedBuiltinTask : public PeriodicTask {
public:
    explicit BlinkLedBuiltinTask(unsigned long intervalMs = 100);

    void setup() override;
    void tick() override;
};

class ColorWheelRgbTask : public PeriodicTask {
public:
    explicit ColorWheelRgbTask(unsigned long intervalMs = 5);

    void setup() override;
    void tick() override;

private:
    float fR = 0, fG = 0, fB = 0, fH = 0, fS = 1, fV = 1;
};
