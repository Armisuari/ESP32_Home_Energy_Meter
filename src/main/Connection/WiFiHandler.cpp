#include "WiFiDefinition.h"
#include "WiFiHandler.h"

WiFiHandler::WiFiHandler(/* args */)
{
}

WiFiHandler::~WiFiHandler()
{
}

void WiFiHandler::setup(const char *ssid_, const char *password_)
{
    WiFi.begin(ssid_, password_);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        ESP_LOGD(WIFIHANDLERTAG, "Connecting to WiFi...");
        // Serial.println("Connecting to WiFi...");
    }

    ESP_LOGD(WIFIHANDLERTAG, "Connected to WiFi");
    // ESP_LOGD(WIFIHANDLERTAG, "IP address: " + WiFi.localIP().toString());
    Serial.println("[WIFIHANDLER] IP address: " + WiFi.localIP().toString());

    // create task for this handler
    xTaskCreate(&WiFiHandler::_staticTaskFunc, 
                CONFIG_WIFI_HANDLER_TASK_NAME, 
                CONFIG_WIFI_HANDLER_TASK_STACK, 
                this, 
                CONFIG_WIFI_HANDLER_TASK_PRIO, 
                &_taskHandle);
}

/* STATIC */ void WiFiHandler::_staticTaskFunc(void *pvParam)
{
    WiFiHandler *handler = reinterpret_cast<WiFiHandler *>(pvParam);
    handler->_taskFunc();
}

void WiFiHandler::_taskFunc()
{
    while (1)
    {
        if (WiFi.status() != WL_CONNECTED)
            ESP_LOGD(WIFIHANDLERTAG,"Reconnecting to WiFi...");
    }
    vTaskDelete(NULL);
}