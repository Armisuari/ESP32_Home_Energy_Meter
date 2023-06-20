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
#include "Connection/WiFiHandler.h"
#include "Server/ServerHandler.h"
#include "Peripherals/PZEM004t_.h"
#include "Peripherals/LCDManager.h"
#include "Peripherals/Utilities.h"

WiFiHandler wifi;
PZEM004t_ sensor;
LCDManager lcd(0x27, 0x3F, 16, 2, 16, 2);
Relay relay;

void calcBalance();
void taskFunc(void *pvParam);

void setup()
{
    Serial.begin(115200);
    Serial.println(ssid);
    wifi.setup(ssid, password);
    setup_server();
    sensor.begin();
    lcd.begin();
    relay.begin();

    lcd.clearDisplays();
    lcd.displayMessage(0, 0, "Preparing", "preparing");
    lcd.displayMessage(0, 1, "WiFi & Server", "WiFi & Server");

    delay(5000); // wait till server established
    xTaskCreate(taskFunc, "main task", 1024 * 4, NULL, 1, NULL);
}

void loop()
{
    vTaskDelete(NULL);
}

unsigned long PREVIOUS_MILLIS_HOURLY;
unsigned long PREVIOUS_MILLIS_SECONDLY;
void calcBalance()
{
    PZEMData_t cost;
    if (millis() - PREVIOUS_MILLIS_HOURLY >= CONFIG_CALCULATION_INTERVAL_H)
    {
        PREVIOUS_MILLIS_HOURLY = millis();

        data.balance1 -= cost.energy[CONFIG_KOST_PERTAMA];
        data.balance2 -= cost.energy[CONFIG_KOST_KEDUA];

        saveValue("/SALDO_KAMAR_1", data.balance1);
        saveValue("/SALDO_KAMAR_2", data.balance2);
    }

    if (millis() - PREVIOUS_MILLIS_SECONDLY >= CONFIG_CALCULATION_INTERVAL_S)
    {
        PREVIOUS_MILLIS_SECONDLY = millis();

        if (data.balance1 <= 0)
        {
            data.balance1 = 0;
            relay.off(Relay1);
        }
        else
        {
            relay.on(Relay1);
        }

        if (data.balance2 <= 0)
        {
            data.balance2 = 0;
            relay.off(Relay2);
        }
        else
        {
            relay.on(Relay2);
        }
    }
}

void taskFunc(void *pvParam)
{
    ESP_LOGD(MAINTAG, "Main Task Started !");
    String dataKamar1, dataKamar2;

    lcd.clearDisplays();

    while (1)
    {
        calcBalance();
        lcd.displayMessage(0, 0, "Kamar 1", "Kamar 2");

        dataKamar1 = String(data.balance1) + " Wh";
        dataKamar2 = String(data.balance2) + " Wh";

        lcd.displayMessage(0, 1, dataKamar1.c_str(), dataKamar2.c_str());
        // vTaskDelay(300);
    }
}