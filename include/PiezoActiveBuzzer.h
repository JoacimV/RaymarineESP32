#ifndef PIEZO_ACTIVE_BUZZER_H
#define PIEZO_ACTIVE_BUZZER_H

#include "BuzzerInterface.h"

/**
 * Arduino-based implementation for active piezo buzzer
 * Uses GPIO pins and Arduino timing functions
 */
class PiezoActiveBuzzer : public BuzzerInterface
{
private:
    int pin;
    bool isActive;

public:
    /**
     * Constructor
     * @param buzzerPin GPIO pin number where buzzer is connected
     */
    PiezoActiveBuzzer(int buzzerPin);

    /**
     * Initialize the buzzer (sets up the pin)
     * Call this in setup()
     */
    void begin() override;

    /**
     * Produce a short beep sound
     * @param duration Duration of beep in milliseconds (default: 100ms)
     */
    void beep(unsigned long duration = 100) override;

    /**
     * Turn buzzer on continuously
     */
    void on() override;

    /**
     * Turn buzzer off
     */
    void off() override;

    /**
     * Check if buzzer is currently active
     * @return true if buzzer is on, false otherwise
     */
    bool isOn() const override;
};

#endif // PIEZO_ACTIVE_BUZZER_H
