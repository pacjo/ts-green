#include "DHT.h"
#include "dht_utils.h"

DHT dht(DHT_PIN, DHT_TYPE);

void setupDht() {
    dht.begin();
}

HumidityReading* takeHumidity() {
    float humidity = dht.readHumidity();
    return new HumidityReading(humidity);
}

TemperatureReading* takeTemperature() {
    float temperature = dht.readTemperature();
    return new TemperatureReading(temperature);
}
