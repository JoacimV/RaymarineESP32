#include "RaymarinePilot.h"
#include <NMEA2000_mcp.h>

// Initialize static member - Raymarine source address
int RaymarinePilot::PilotSourceAddress = 204;

RaymarinePilot::RaymarinePilot(tNMEA2000 &nmea2000Instance)
    : AutopilotInterface(nmea2000Instance)
{
    PilotSourceAddress = 204;
}

void RaymarinePilot::SendTurn(TurnDirections direction)
{
    int command;
    if (direction == TURN_STARBOARD)
    {
        command = PLUS_10;
    }
    else
    {
        command = MINUS_10;
    }

    tN2kMsg N2kMsg;
    // Raymarine EV-100/200 specific key command protocol
    byte commandByte0, commandByte1;
    commandByte0 = command >> 8;
    commandByte1 = command & 0xff;

    N2kMsg.SetPGN(126720UL);
    N2kMsg.Priority = 7;
    N2kMsg.Destination = RaymarinePilot::PilotSourceAddress;

    N2kMsg.AddByte(0x3b);
    N2kMsg.AddByte(0x9f);
    N2kMsg.AddByte(0xf0);
    N2kMsg.AddByte(0x81);
    N2kMsg.AddByte(0x86);
    N2kMsg.AddByte(0x21);
    N2kMsg.AddByte(commandByte0);
    N2kMsg.AddByte(commandByte1);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xc1);
    N2kMsg.AddByte(0xc2);
    N2kMsg.AddByte(0xcd);
    N2kMsg.AddByte(0x66);
    N2kMsg.AddByte(0x80);
    N2kMsg.AddByte(0xd3);
    N2kMsg.AddByte(0x42);
    N2kMsg.AddByte(0xb1);
    N2kMsg.AddByte(0xc8);
    nmea2000.SendMsg(N2kMsg);
}

void RaymarinePilot::SendSetMode(PilotModes mode)
{
    tN2kMsg N2kMsg;
    // Raymarine EV-100/200 specific mode setting protocol
    N2kMsg.SetPGN(126208UL);
    N2kMsg.Priority = 3;
    N2kMsg.Destination = PilotSourceAddress;
    N2kMsg.AddByte(1);
    N2kMsg.AddByte(0x63);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0x00);
    N2kMsg.AddByte(0xf8);
    N2kMsg.AddByte(0x04);
    N2kMsg.AddByte(0x01);
    N2kMsg.AddByte(0x3b);
    N2kMsg.AddByte(0x07);
    N2kMsg.AddByte(0x03);
    N2kMsg.AddByte(0x04);
    N2kMsg.AddByte(0x04);

    switch (mode)
    {
    case MODE_STANDBY:
        N2kMsg.AddByte(0x00);
        N2kMsg.AddByte(0x00);
        break;
    case MODE_AUTO:
        N2kMsg.AddByte(0x40);
        N2kMsg.AddByte(0x00);
        break;
    }

    N2kMsg.AddByte(0x05);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    nmea2000.SendMsg(N2kMsg);
}