#include "PiezoActiveBuzzer.h"
#include <Arduino.h>

PiezoActiveBuzzer::PiezoActiveBuzzer(int buzzerPin) : pin(buzzerPin), isActive(false)
{
}

void PiezoActiveBuzzer::begin()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    isActive = false;
}

void PiezoActiveBuzzer::beep(unsigned long duration)
{
    on();
    delay(duration);
    off();
}

void PiezoActiveBuzzer::on()
{
    digitalWrite(pin, HIGH);
    isActive = true;
}

void PiezoActiveBuzzer::off()
{
    digitalWrite(pin, LOW);
    isActive = false;
}

bool PiezoActiveBuzzer::isOn() const
{
    return isActive;
}
