#ifndef RAYMARINE_PILOT_H
#define RAYMARINE_PILOT_H

#include "AutopilotInterface.h"

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

private:
    static int PilotSourceAddress; // Raymarine-specific source address

    // Private helper method for key commands
    void KeyCommand(tN2kMsg &N2kMsg, uint16_t command);

public:
    // Constructor - takes NMEA2000 reference
    RaymarinePilot(tNMEA2000 &nmea2000Instance);

    // Implement pure virtual methods from AutopilotInterface
    void SetMode(tN2kMsg &N2kMsg, PilotModes mode) override;
    void SendKeyCommand(uint16_t command) override;
    void SendSetMode(PilotModes mode) override;
};

#endif // RAYMARINE_PILOT_H