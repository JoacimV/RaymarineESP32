#ifndef BUZZER_INTERFACE_H
#define BUZZER_INTERFACE_H

/**
 * Abstract interface for buzzer implementations
 * Provides audio feedback without platform dependencies
 */
class BuzzerInterface
{
public:
    virtual ~BuzzerInterface() = default;

    /**
     * Initialize the buzzer hardware
     * Call this in setup()
     */
    virtual void begin() = 0;

    /**
     * Produce a short beep sound
     * @param duration Duration of beep in milliseconds (default: 100ms)
     */
    virtual void beep(unsigned long duration = 100) = 0;

    /**
     * Turn buzzer on continuously
     */
    virtual void on() = 0;

    /**
     * Turn buzzer off
     */
    virtual void off() = 0;

    /**
     * Check if buzzer is currently active
     * @return true if buzzer is on, false otherwise
     */
    virtual bool isOn() const = 0;
};

#endif // BUZZER_INTERFACE_H
