#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <EEPROM.h>

// Replace with your network credentials
const char* ssid = "Tangga 1";
const char* password = "bandungsatu";

WebServer server(80);

int selectedPrice = 0;
const int prices[] = {20000, 50000, 100000};
const int numPrices = sizeof(prices) / sizeof(prices[0]);

void writePriceToEEPROM() {
  EEPROM.begin(sizeof(selectedPrice));
  EEPROM.put(0, selectedPrice);
  EEPROM.commit();
  EEPROM.end();
}

void readPriceFromEEPROM() {
  EEPROM.begin(sizeof(selectedPrice));
  EEPROM.get(0, selectedPrice);
  EEPROM.end();
}

void handleRoot() {
  readPriceFromEEPROM();

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
  html += "<h1>Pilih Nominal Pulsa Token:</h1>";
  html += "<p>Total Token Sekarang: " + String(selectedPrice) + "</p>";
  html += "<form method='get' action='/setprice'>";
  html += "<select name='price'>";

  for (int i = 0; i < numPrices; i++) {
    html += "<option value='" + String(prices[i]) + "'>" + String(prices[i]) + "</option>";
  }

  html += "</select>";
  html += "<br><br>";
  html += "<input type='submit' value='Pilih'>";
  html += "</form>";
  html += "<br>";
  html += "<form method='get' action='/reset'>";
  html += "<input type='submit' value='Reset Token'>";
  html += "</form>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleSetPrice() {
  String price = server.arg("price");
  int increment = price.toInt();
  selectedPrice += increment;
  writePriceToEEPROM();

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
  html += "<h1>Berhasil Membeli Token:</h1>";
  html += "<p>Token Dibeli: " + String(increment) + "</p>";
  html += "<p>Total Token: " + String(selectedPrice) + "</p>";
  html += "<a href='/'>Kembali</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleReset() {
  selectedPrice = 0;
  writePriceToEEPROM();

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
  html += "<h1>Token Direset:</h1>";
  html += "<p>Token Direset to 0</p>";
  html += "<a href='/'>Kembali</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleGetPrice() {
  readPriceFromEEPROM();

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
  html += "<h1>Current Price:</h1>";
  html += "<p>Price: " + String(selectedPrice) + "</p>";
  html += "<a href='/'>Kembali</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/setprice", handleSetPrice);
  server.on("/reset", handleReset);
  server.on("/getprice", handleGetPrice);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
