#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDManager
{
private:
  LiquidCrystal_I2C lcd1;
  LiquidCrystal_I2C lcd2;

public:
  LCDManager(uint8_t lcd1Addr, uint8_t lcd2Addr, uint8_t lcd1Cols, uint8_t lcd1Rows, uint8_t lcd2Cols, uint8_t lcd2Rows)
      : lcd1(lcd1Addr, lcd1Cols, lcd1Rows), lcd2(lcd2Addr, lcd2Cols, lcd2Rows) {}

  void begin();
  void displayMessage(int col, int row, const char *msg1, const char *msg2);
  void clearDisplays();
};