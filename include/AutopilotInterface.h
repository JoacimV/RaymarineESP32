#ifndef AUTOPILOT_INTERFACE_H
#define AUTOPILOT_INTERFACE_H

#include <functional>

/**
 * Abstract base class for autopilot implementations
 * Defines the common interface that all autopilot brands must implement
 */
class AutopilotInterface
{
public:
    // Common autopilot modes (all brands support these)
    enum PilotModes
    {
        MODE_STANDBY = 0,
        MODE_AUTO = 1
    };

    enum TurnCommands
    {
        TURN_LEFT = 0,
        TURN_RIGHT = 1,
        TURN_LEFT_TEN = 2,
        TURN_RIGHT_TEN = 3
    };

    // Constructor
    AutopilotInterface() {}

    // Virtual destructor (important for proper cleanup)
    virtual ~AutopilotInterface() = default;

    // Pure virtual methods - must be implemented by each brand
    virtual void setMode(PilotModes mode) = 0;
    virtual void turn(TurnCommands command) = 0;
    /**
     * Will be called from the main loop to allow the autopilot to perform
     * any periodic tasks, such as sending heartbeat messages.
     */
    virtual void update() = 0;
};

#endif // AUTOPILOT_INTERFACE_H