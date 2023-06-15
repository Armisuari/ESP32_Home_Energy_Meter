#pragma once

#include <WiFi.h>
#include <WiFiClient.h>

class WiFiHandler
{
private:
    /* data */
    TaskHandle_t _taskHandle;
    static void _staticTaskFunc(void *pvParam);
    void _taskFunc();

public:
    WiFiHandler(/* args */);
    ~WiFiHandler();

    void setup(const char* ssid_, const char* password_);
};
