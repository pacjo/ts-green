#pragma once

#include <Arduino.h>

/**
 * Generic periodic FreeRTOS task.
 */
class PeriodicTask {
public:
    virtual ~PeriodicTask() = default;

    /** One-time setup/configuration. */
    virtual void setup() = 0;

    /** Called every @ref intervalMs milliseconds. */
    virtual void tick() = 0;

    /**
     * FreeRTOS task entry-point.
     *
     * @param pvParameters a pointer to the PeriodicTask instance.
     */
    static void runTask(void* pvParameters) {
        PeriodicTask* self = static_cast<PeriodicTask*>(pvParameters);
        self->setup();
        while (true) {
            self->tick();
            vTaskDelay(pdMS_TO_TICKS(self->intervalMs));
        }
    }

protected:
    explicit PeriodicTask(unsigned long intervalMs) : intervalMs(intervalMs) {}
    unsigned long intervalMs;
};
