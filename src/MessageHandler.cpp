#include "MessageHandler.h"
#include <Arduino.h>

// Handle incoming NMEA2000 messages
void MessageHandler::HandleNMEA2000Msg(const tN2kMsg &N2kMsg) {
    switch (N2kMsg.PGN) {
        case 65379L:  // Autopilot status
            ParseAutopilotStatus(N2kMsg);
            break;
        // Add more PGN handlers here as needed
        default:
            // Uncomment for debugging unknown messages
            // Serial.print("📡 Unknown PGN: ");
            // Serial.println(N2kMsg.PGN);
            break;
    }
}

// Parse autopilot status message (PGN 65379)
void MessageHandler::ParseAutopilotStatus(const tN2kMsg &N2kMsg) {
    int Index = 2;
    unsigned char Mode = N2kMsg.GetByte(Index);
    unsigned char Submode = N2kMsg.GetByte(Index);

    Serial.print("🚢 PILOT: ");
    if (Mode == 0x00 && Submode == 0x00) {
        Serial.println("STANDBY");
    }
    else if (Mode == 0x40 && Submode == 0x00) {
        Serial.println("AUTO");
    }
    else {
        Serial.print("Mode=0x");
        Serial.print(Mode, HEX);
        Serial.print(" Sub=0x");
        Serial.println(Submode, HEX);
    }
}