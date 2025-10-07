#ifndef RAYMARINE_PILOT_H
#define RAYMARINE_PILOT_H

#include "AutopilotInterface.h"
#include <N2kMessages.h>

// Forward declaration
class tNMEA2000;

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
    tNMEA2000 &nmea2000;           // Reference to NMEA2000 instance

public:
    // Constructor - takes NMEA2000 reference
    RaymarinePilot(tNMEA2000 &nmea2000Instance);

    // Implement pure virtual methods from AutopilotInterface
    virtual void setMode(PilotModes mode) override;
    virtual void turn(TurnCommands command) override;
};

#endif // RAYMARINE_PILOT_H