/**
 * @file main.cpp
 * @author Arief Nur Misuaro (armisuari)
 * @brief This is the main file of the firmware. Here lays almost all tasks to make 
 * it easier to track any wierd behaviors
 * @version 0.1
 * @date 2023-05-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//====================================================

#include <Arduino.h>

/*

    1. WifiHandler
    2. ServerHandler
    3. SensorHandler
        a. get energy usage data
        b. Token to energy balance convertion

        currentPowerUsage = 25 W
        EnergyBalance = 3000 KWh
        currentEnergyUsage = 0.025 kWh

        EnergyBalance = EnergyBalance - currentEnergyUsage

*/

#include "Config.h"
#include "Server/ServerHandler.h"
#include "Connection/WiFiHandler.h"

const char* ssid = "Tangga 1";
const char* password = "bandungsatu";

WiFiHandler wifi;

void setup()
{
    Serial.begin(115200);
    wifi.setup(ssid, password);
    setup_server();
}

void loop()
{
    vTaskDelete(NULL);
}