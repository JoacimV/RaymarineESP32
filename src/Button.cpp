#include "Button.h"

Button::Button(int pin, unsigned long debounceDelay)
{
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    this->lastInterruptTime = 0;
}

// Initialize hardware + set callback! 🚀
void Button::setup(const LambdaCallback &callback)
{
    pinMode(pin, INPUT_PULLUP);
    // Attach interrupt on FALLING edge (button press with pull-up)
    attachInterruptArg(digitalPinToInterrupt(pin), handleInterrupt, this, FALLING);
    onClickLambdaCallback = callback;
}

// Static interrupt handler - calls instance method
void IRAM_ATTR Button::handleInterrupt(void *arg)
{
    Button *button = static_cast<Button *>(arg);
    button->onInterrupt();
}

// Instance interrupt handler with debouncing
void IRAM_ATTR Button::onInterrupt()
{
    unsigned long currentTime = millis();

    // Debounce check
    if (currentTime - lastInterruptTime > debounceDelay)
    {
        lastInterruptTime = currentTime;
        onClickLambdaCallback();
    }
}