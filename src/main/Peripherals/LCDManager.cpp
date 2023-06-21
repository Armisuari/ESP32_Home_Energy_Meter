#include "LCDManager.h"

void LCDManager::begin()
{
    Wire.begin();
    lcd1.init();
    lcd2.init();

    lcd1.backlight();
    lcd2.backlight();

    lcd1.setCursor(0, 0);
    lcd1.print("LCD 1 Initialized");

    lcd2.setCursor(0, 0);
    lcd2.print("LCD 2 Initialized");
}

void LCDManager::displayMessage(int col, int row, const char *msg1, const char *msg2)
{
    lcd1.setCursor(col, row);
    lcd1.print(msg1);

    lcd2.setCursor(col, row);
    lcd2.print(msg2);
}

void LCDManager::clearDisplays()
{

    lcd1.noBacklight();
    lcd2.noBacklight();

    lcd1.clear();
    lcd2.clear();
    
    lcd1.backlight();
    lcd2.backlight();
}