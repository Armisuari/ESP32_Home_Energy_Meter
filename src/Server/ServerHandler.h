#pragma once

#include <Arduino.h>
#include <WebServer.h>
// #include <EEPROM.h>
#include <Effortless_SPIFFS.h>

#include "ServerDefinition.h"
#include <vector>

typedef struct
{
    float balance1; // in kwh units
    float balance2;
    const int prices[3] = {20000, 50000, 100000};
    const int numPrices = sizeof(prices) / sizeof(prices[0]);
} ServerData_t;

class ServerHandler
{
public:
    ServerHandler(/* args */);
    ~ServerHandler();

    static void _staticTaskFunc(void *pvParam);
    void _taskFunc();
};

class FsManager
{
public:
    // bool begin(eSPIFFS *);

    bool listFiles(const char *);

    // bool createDir(const char *);
    // bool deleteDir(const char *);
    bool deleteFile(const char *);
    // bool deleteFiles(const char *);
};

WebServer server(80);
ServerData_t data;
eSPIFFS fileSystem(&Serial); // Optional - allow the methods to print debug
FsManager fsManager;

bool FsManager::listFiles(const char *path)
{
    File root = SPIFFS.open(path);
    File file = root.openNextFile();

    if (!file)
    {
        Serial.printf("\"%s\" directory empty\n", path);
        return false;
    }

    while (file)
    {
        Serial.print("FILE: ");
        Serial.println(file.name());

        file = root.openNextFile();
    }

    return true;
}

bool FsManager::deleteFile(const char *path)
{
    return SPIFFS.remove(path);
}

// void writeBalanceToEEPROM(int balance, size_t addr)
// {
//     EEPROM.begin(sizeof(balance));
//     EEPROM.put(addr, balance);
//     EEPROM.commit();
//     EEPROM.end();
// }

// int readBalanceFromEEPROM(size_t addr)
// {
//     int balance;
//     EEPROM.begin(sizeof(balance));
//     EEPROM.get(addr, balance);
//     EEPROM.end();
//     return balance;
// }

// void saveValue(const char *filename, float value)
// {
//     fileSystem.appendToFile(filename, String(value).c_str());
// }

// int loadValue(const char *filename)
// {
//     String value;
//     fsManager.listFiles("/");
//     fileSystem.openFromFile(filename, value);
//     return value.toFloat();
// }

void saveValue(String filename_, float value)
{
    // String filename_ = "/SALDO_KAMAR_1.txt";
    // String value = String(data.balance1);
    fsManager.deleteFile(filename_.c_str());
    Serial.printf("value: %f\n", value);
    fileSystem.appendToFile(filename_.c_str(), String(value).c_str());
}

float loadValue(String filename_)
{
    // String filename_ = "/SALDO_KAMAR_1.txt";
    String value;
    fsManager.listFiles("/");
    fileSystem.openFromFile(filename_.c_str(), value);
    return value.toFloat();
}

void handleRoot()
{
    // data.balance1 = readBalanceFromEEPROM(0);
    // data.balance2 = readBalanceFromEEPROM(4);

    data.balance1 = loadValue("/SALDO_KAMAR_1.txt");
    data.balance2 = loadValue("/SALDO_KAMAR_2.txt");

    String html = "<html><head>";
    html += "<style>";
    html += "body {";
    html += "  font-family: Arial, sans-serif;";
    html += "  background-color: #F1F1F1;";
    html += "}";
    html += "h1 {";
    html += "  color: #333333;";
    html += "}";
    html += "form {";
    html += "  margin-top: 20px;";
    html += "}";
    html += "select {";
    html += "  padding: 5px;";
    html += "  font-size: 16px;";
    html += "  border-radius: 5px;";
    html += "  border: 1px solid #CCCCCC;";
    html += "}";
    html += "input[type='submit'] {";
    html += "  padding: 8px 12px;";
    html += "  font-size: 16px;";
    html += "  background-color: #4CAF50;";
    html += "  border: none;";
    html += "  color: white;";
    html += "  border-radius: 5px;";
    html += "  cursor: pointer;";
    html += "}";
    html += "a.button {";
    html += "  display: inline-block;";
    html += "  background-color: #4CAF50;";
    html += "  color: white;";
    html += "  padding: 8px 12px;";
    html += "  text-decoration: none;";
    html += "  border-radius: 5px;";
    html += "}";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Beli Token Listrik:</h1>";
    html += "<p>Saldo Token Kamar 1: " + String(data.balance1) + " Wh" + "</p>";
    html += "<p>Saldo Token kamar 2: " + String(data.balance2) + " Wh" + "</p>";
    html += "<form method='get' action='/setprice1'>";
    html += "<select name='price1'>";

    for (int i = 0; i < data.numPrices; i++)
    {
        html += "<option value='" + String(data.prices[i]) + "'>" + String(data.prices[i]) + "</option>";
    }

    html += "</select>";
    html += "<br><br>";
    html += "<input type='submit' value='Submit Token'>";
    html += "</form>";
    html += "<br>";
    html += "<form method='get' action='/setprice2'>";
    html += "<select name='price2'>";

    for (int i = 0; i < data.numPrices; i++)
    {
        html += "<option value='" + String(data.prices[i]) + "'>" + String(data.prices[i]) + "</option>";
    }

    html += "</select>";
    html += "<br><br>";
    html += "<input type='submit' value='Submit Token'>";
    html += "</form>";
    html += "<br>";
    html += "<form method='get' action='/reset'>";
    html += "<input type='submit' value='Reset Token'>";
    html += "</form>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleSetBalance1()
{
    String price = server.arg("price1");
    int increment = price.toInt() / CONFIG_SERVER_HANDLER_SERVER_PRICE;

    ESP_LOGD(SERVERHANDLERTAG, "increment = %d", increment);

    data.balance1 += increment;

    ESP_LOGD(SERVERHANDLERTAG, "data.balance1 = %f", data.balance1);

    // writeBalanceToEEPROM(data.balance1, 0);

    saveValue("/SALDO_KAMAR_1.txt", data.balance1);

    String html = "<html><head>";
    html += "<style>";
    html += "body {";
    html += "  font-family: Arial, sans-serif;";
    html += "  background-color: #F1F1F1;";
    html += "}";
    html += "h1 {";
    html += "  color: #333333;";
    html += "}";
    html += "p {";
    html += "  margin-bottom: 20px;";
    html += "}";
    html += "a.button {";
    html += "  display: inline-block;";
    html += "  background-color: #4CAF50;";
    html += "  color: white;";
    html += "  padding: 8px 12px;";
    html += "  text-decoration: none;";
    html += "  border-radius: 5px;";
    html += "}";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Balance Selected:</h1>";
    html += "<p>Balance Increment for Balance 1: " + String(increment) + "</p>";
    html += "<p>New Balance for Balance 1: " + String(data.balance1) + " Wh" + "</p>";
    //   html += "<p>Current Saved Balance 2: " + String(data.balance2) + "</p>";
    html += "<a href='/'>Go Back</a>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleSetBalance2()
{
    String price = server.arg("price2");
    int increment = price.toInt() / CONFIG_SERVER_HANDLER_SERVER_PRICE;
    data.balance2 += increment;

    ESP_LOGD(SERVERHANDLERTAG, "data.balance2 = %f", data.balance2);

    // writeBalanceToEEPROM(data.balance2, 4);

    saveValue("/SALDO_KAMAR_2.txt", data.balance2);

    String html = "<html><head>";
    html += "<style>";
    html += "body {";
    html += "  font-family: Arial, sans-serif;";
    html += "  background-color: #F1F1F1;";
    html += "}";
    html += "h1 {";
    html += "  color: #333333;";
    html += "}";
    html += "p {";
    html += "  margin-bottom: 20px;";
    html += "}";
    html += "a.button {";
    html += "  display: inline-block;";
    html += "  background-color: #4CAF50;";
    html += "  color: white;";
    html += "  padding: 8px 12px;";
    html += "  text-decoration: none;";
    html += "  border-radius: 5px;";
    html += "}";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Price Selected:</h1>";
    html += "<p>Price Increment for Price 2: " + String(increment) + "</p>";
    html += "<p>New Price for Price 2: " + String(data.balance2) + " Wh" + "</p>";
    html += "<a href='/'>Go Back</a>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleReset()
{
    data.balance1 = 0;
    data.balance2 = 0;
    // writeBalanceToEEPROM(data.balance1, 0);
    // writeBalanceToEEPROM(data.balance2, 4);

    saveValue("/SALDO_KAMAR_1.txt", data.balance1);
    saveValue("/SALDO_KAMAR_2.txt", data.balance2);

    String html = "<html><head>";
    html += "<style>";
    html += "body {";
    html += "  font-family: Arial, sans-serif;";
    html += "  background-color: #F1F1F1;";
    html += "}";
    html += "h1 {";
    html += "  color: #333333;";
    html += "}";
    html += "p {";
    html += "  margin-bottom: 20px;";
    html += "}";
    html += "a.button {";
    html += "  display: inline-block;";
    html += "  background-color: #4CAF50;";
    html += "  color: white;";
    html += "  padding: 8px 12px;";
    html += "  text-decoration: none;";
    html += "  border-radius: 5px;";
    html += "}";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Prices Reset:</h1>";
    html += "<p>Prices Reset to 0</p>";
    html += "<a href='/'>Go Back</a>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

bool setup_server()
{
    // data.balance1 = readBalanceFromEEPROM(0);
    // data.balance2 = readBalanceFromEEPROM(1);

    data.balance1 = loadValue("/SALDO_KAMAR_1.txt");
    data.balance2 = loadValue("/SALDO_KAMAR_2.txt");

    if (!SPIFFS.begin(true))
    {
        ESP_LOGE(SPIFFSTAG, "Failed to mount SPIFFSFS");
        return false;
    }

    server.on("/", handleRoot);
    server.on("/setprice1", handleSetBalance1);
    server.on("/setprice2", handleSetBalance2);
    server.on("/reset", handleReset);

    server.begin();
    ESP_LOGI(SERVERHANDLERTAG, "HTTP server started");

    // create task for this handler
    xTaskCreate(&ServerHandler::_staticTaskFunc,
                CONFIG_SERVER_HANDLER_TASK_NAME,
                CONFIG_SERVER_HANDLER_TASK_STACK,
                NULL,
                CONFIG_SERVER_HANDLER_TASK_PRIO,
                NULL);

    return true;
}

ServerHandler::ServerHandler(/* args */)
{
}

ServerHandler::~ServerHandler()
{
}

/* STATIC */ void ServerHandler::_staticTaskFunc(void *pvParam)
{
    ServerHandler *handler = reinterpret_cast<ServerHandler *>(pvParam);
    handler->_taskFunc();
}

void ServerHandler::_taskFunc()
{
    ESP_LOGD(SERVERHANDLERTAG, "Server Handler Task Started");
    unsigned long prevMillis = 0;
    while (1)
    {
        server.handleClient();

        if (millis() - prevMillis >= 1000UL)
        {
            prevMillis = millis();
            // Serial.printf("Balance 1: %f\nBalance 2: %f\n",
            //               data.balance1, data.balance2);
            // fsManager.listFiles("/");

            // String filename_ = "/SALDO_KAMAR_1.txt";
            // String value;

            fsManager.listFiles("/");
            // fileSystem.openFromFile(filename_.c_str(), value);
            // // Serial.printf("value_readed: %s\n", value);
            // Serial.println("value_readed: " + value);
            // data.balance1 = value.toFloat();
            // Serial.printf("Saldo kamar 1: %f\n", data.balance1);
        }
    }
    vTaskDelete(NULL);
}