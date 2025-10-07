#ifndef ON_HANDLER_H
#define ON_HANDLER_H

#include <NMEA2000_mcp.h>

// Forward declaration
class AutopilotInterface;

/**
 * Handler for the "On" button press
 * Executes the turn-on functionality when called
 */
class OnHandler
{
private:
    static AutopilotInterface *autopilot;

public:
    // Constructor
    OnHandler(tNMEA2000_mcp &nmea2000);

    // Virtual destructor for proper cleanup
    virtual ~OnHandler() = default;

    // Execute the handler action
    void execute();
};

#endif // ON_HANDLER_H