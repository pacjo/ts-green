#include "DHT.h"
#include "dht_utils.h"

DHT dht(DHT_PIN, DHT_TYPE);

void setupDht() {
    dht.begin();
}
