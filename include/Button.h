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
    volatile bool clickPending;
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

    // Run deferred click callbacks outside interrupt context.
    void process();
};

#endif // BUTTON_H