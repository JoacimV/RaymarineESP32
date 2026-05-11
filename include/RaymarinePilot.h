#ifndef RAYMARINE_PILOT_H
#define RAYMARINE_PILOT_H

#include <stdint.h>
#include "AutopilotInterface.h"

// Forward declaration
class tNMEA2000_mcp;

// External NMEA2000 instance (defined in RaymarinePilot.cpp)
extern tNMEA2000_mcp NMEA2000;

/**
 * Raymarine-specific autopilot implementation
 * Implements the AutopilotInterface for Raymarine EV-100/200 series autopilots
 */
class RaymarinePilot : public AutopilotInterface
{
public:
    // Raymarine-specific key command constants
    static const uint16_t PLUS_10 = 0x08F7;  // Starboard 10°
    static const uint16_t MINUS_10 = 0x06F9; // Port 10°
    static const uint16_t PILOT_SOURCE_ADDRESS = 204;

private:
    static int PilotSourceAddress; // Raymarine-specific source address
    volatile PilotState ObservedState;

public:
    // Constructor
    RaymarinePilot();

    // Static method to initialize NMEA2000 for Raymarine EV-100 use
    static bool initializeNMEA2000();

    // Implement pure virtual methods from AutopilotInterface
    virtual void setMode(PilotModes mode) override;
    virtual void setObservedState(PilotState state) override;
    virtual PilotState getState() const override;
    virtual void turn(TurnCommands command) override;
    virtual void update() override;
};

#endif // RAYMARINE_PILOT_H