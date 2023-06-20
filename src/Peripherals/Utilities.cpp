#include "Utilities.h"

Relay::Relay()
{
}

bool Relay::begin()
{
    pinMode(Relay1, OUTPUT);
    pinMode(Relay2, OUTPUT);

    return true;
}

void Relay::on(size_t pin)
{
    digitalWrite(pin, LOW);
}

void Relay::off(size_t pin)
{
    digitalWrite(pin, HIGH);
}

bool Buzzer::begin()
{
    pinMode(buzzer, OUTPUT);
    return true;
}

void Buzzer::beep(size_t delay_)
{
    digitalWrite(buzzer, HIGH);
    delay(delay_);
    digitalWrite(buzzer, LOW);
}

void Buzzer::loop(size_t count)
{
    for (size_t i; i<=count; i++)
    {
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
    }
}