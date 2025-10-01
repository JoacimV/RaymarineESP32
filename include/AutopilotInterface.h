#ifndef AUTOPILOT_INTERFACE_H
#define AUTOPILOT_INTERFACE_H

#include <Arduino.h>
#include <functional>
#include <N2kMessages.h>

// Forward declarations
class tNMEA2000;

/**
 * Abstract base class for autopilot implementations
 * Defines the common interface that all autopilot brands must implement
 */
class AutopilotInterface
{
protected:
    tNMEA2000 &nmea2000; // Reference to NMEA2000 instance

public:
    // Common autopilot modes (all brands support these)
    enum PilotModes
    {
        MODE_STANDBY = 0,
        MODE_AUTO = 1
    };

    // Constructor - takes NMEA2000 reference
    AutopilotInterface(tNMEA2000 &nmea2000Instance) : nmea2000(nmea2000Instance) {}

    // Virtual destructor (important for proper cleanup)
    virtual ~AutopilotInterface() = default;

    // Pure virtual methods - must be implemented by each brand
    virtual void SetMode(tN2kMsg &N2kMsg, PilotModes mode) = 0;
    virtual void SendKeyCommand(uint16_t command) = 0;
    virtual void SendSetMode(PilotModes mode) = 0;
};

#endif // AUTOPILOT_INTERFACE_H