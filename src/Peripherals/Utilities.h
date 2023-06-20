#pragma once

#include <Arduino.h>

#define Relay1 2
#define Relay2 4
#define buzzer 6

class Relay
{
public:
    Relay();
    bool begin();
    void on(size_t pin);
    void off(size_t pin);
};

class Buzzer
{
public:
    bool begin();
    void beep(size_t delay_);
    void loop(size_t count);
};