#include <Arduino.h>
#include "data/sensor_reading.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "led_utils.h"
#include "dht_utils.h"
#include "networking/wifi_utils.h"
#include "photodiode_utils.h"
#include "soil_utils.h"

void blinkLedBuiltin(void* pvParameters) {
    pinMode(LED_BUILTIN, OUTPUT);

    int delay_ms = 100;
    while (true) {
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

// TODO: add hsv roll
void colorWheelRgb(void* pvParameters) {
    setupRgbLed();
    float fR = 0, fG = 0, fB = 0, fH = 0, fS = 1, fV = 1;

    int delay_ms = 5;
    while (true) {
        HSVtoRGB(fR, fG, fB, fH, fS, fV);
        fH = fmod(fH + 0.01, 360);

        analogWrite(LED_R, fR);
        analogWrite(LED_G, fG);
        analogWrite(LED_B, fB);

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

void printTempAndHumidity(void* pvParameters) {
    setupDht();

    while (true) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        Serial.print("temp: ");
        Serial.print(temperature);
        Serial.print(",\thumidity: ");
        Serial.println(humidity);

        pushReading(new TemperatureReading(temperature));
        pushReading(new HumidityReading(humidity));

        // delay 500ms
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void printPhotodiode(void* pvParameters) {
    setupPhotodiode();

    while (true) {
        float value = readPhotodiode();
        Serial.print("Protodiode: ");
        Serial.println(value);

        pushReading(new LightReading(value));

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void printSoilMoisture(void* pvParameters) {
    setupSoilMoisture();

    while (true) {
        float value = readSoilMoisture();
        Serial.print("Soil Moisture: ");
        Serial.println(value);

        pushReading(new SoilMoistureReading(value));

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // prepare sensor queue
    setupSensorQueue();

    int sensor_priority = 10;
    xTaskCreate(blinkLedBuiltin, "blinkLedBuiltin", 1024, NULL, sensor_priority, NULL);
    xTaskCreate(colorWheelRgb, "colorWheelRgb", 1024, NULL, sensor_priority, NULL);
    xTaskCreate(printTempAndHumidity, "printTempAndHumidity", 1024, NULL, sensor_priority, NULL);
    xTaskCreate(printPhotodiode, "printPhotodiode", 1024, NULL, sensor_priority, NULL);
    xTaskCreate(printSoilMoisture, "printSoilMoisture", 1024, NULL, sensor_priority, NULL);

    int network_priority = 10;
    xTaskCreate(sendToNetworkTask, "sendToNetwork", 4096, NULL, network_priority, NULL);
}

void loop () { }
