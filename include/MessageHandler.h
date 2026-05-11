#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "AutopilotInterface.h"
#include <N2kMessages.h>

// NMEA2000 Message Handler for autopilot status monitoring
class MessageHandler {
public:
    typedef void (*PilotStateUpdateCallback)(AutopilotInterface::PilotState state);

    // Handle incoming NMEA2000 messages
    static void HandleNMEA2000Msg(const tN2kMsg &N2kMsg);
    static void SetPilotStateUpdateCallback(PilotStateUpdateCallback callback);
    
private:
    static PilotStateUpdateCallback StateUpdateCallback;

    // Parse autopilot status message (PGN 65379)
    static void ParseAutopilotStatus(const tN2kMsg &N2kMsg);
};

#endif // MESSAGE_HANDLER_H