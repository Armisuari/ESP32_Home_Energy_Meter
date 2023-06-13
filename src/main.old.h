#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <EEPROM.h>

// Replace with your network credentials
const char *ssid = "Tangga 1";
const char *password = "bandungsatu";

unsigned long prevMillis = 0;
unsigned long interval = 1000;

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

  String html = "<html><body>";
  html += "<h1>Pilih Nominal Token:</h1>";
  html += "<p>Jumlah Token Sekarang: " + String(selectedPrice) + "</p>";
  html += "<form method='get' action='/setprice'>";
  html += "<select name='price'>";

  for (int i = 0; i < numPrices; i++) {
    html += "<option value='" + String(prices[i]) + "'>" + String(prices[i]) + "</option>";
  }

  html += "</select>";
  html += "<input type='submit' value='Submit'>";
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

  String html = "<html><body>";
  html += "<h1>Berhasil Membeli Token:</h1>";
  html += "<p>Token yang ditambahakan: " + String(increment) + "</p>";
  html += "<p>Total Token Sekarang: " + String(selectedPrice) + "</p>";
  html += "<a href='/'>Kembali ke Beranda</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleReset() {
  selectedPrice = 0;
  writePriceToEEPROM();

  String html = "<html><body>";
  html += "<h1>Token Reset:</h1>";
  html += "<p>Token direset ke 0</p>";
  html += "<a href='/'>Kembali ke Beranda</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleGetPrice() {
  readPriceFromEEPROM();

  String html = "<html><body>";
  html += "<h1>Jumlah Token Sekarang:</h1>";
  html += "<p>Token: " + String(selectedPrice) + "</p>";
  html += "<a href='/'>Kembali ke Beranda</a>";
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

void loop()
{
  server.handleClient();

  if (millis() - prevMillis >= interval)
  {
    prevMillis = millis();
    Serial.printf("Jumlah Token: %d\n", selectedPrice);
  }
}
