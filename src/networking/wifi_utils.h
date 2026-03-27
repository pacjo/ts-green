#pragma once

/*
 * Connect to WiFi network with SSID and password set in wifi_utils.cpp
 */
void connectToWifi();

/*
 * Task that sends sensor readings to the network.
 */
void sendToNetworkTask(void* pvParameters);
