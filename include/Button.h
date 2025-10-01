#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <functional>

typedef std::function<void()> LambdaCallback;

class Button
{
private:
    int pin;
    unsigned long lastInterruptTime;
    unsigned long debounceDelay;
    LambdaCallback onClickLambdaCallback;

    // Static interrupt handler
    static void IRAM_ATTR handleInterrupt(void *arg);

    // Instance interrupt handler
    void IRAM_ATTR onInterrupt();

public:
    // Constructor - auto-initializes the button! 🚀
    Button(int pin, unsigned long debounceDelay = 50);

    // Combined setup: set callback and enable interrupt
    void setup(const LambdaCallback &callback);
};

#endif // BUTTON_H