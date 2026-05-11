#include "RaymarinePilot.h"
#include "MessageHandler.h"
#include <NMEA2000_mcp.h>

#define N2k_SPI_CS_PIN 5

tNMEA2000_mcp NMEA2000(N2k_SPI_CS_PIN, MCP_8MHz);

RaymarinePilot::RaymarinePilot() : AutopilotInterface(), ObservedState(STATE_UNKNOWN), Ready(false)
{
    // Configure NMEA2000 buffers for Raymarine communication
    NMEA2000.SetN2kCANReceiveFrameBufSize(150);
    NMEA2000.SetN2kCANMsgBufSize(10);
    NMEA2000.SetMsgHandler(MessageHandler::HandleNMEA2000Msg);

    // Set Raymarine EV-100 Remote device information
    NMEA2000.SetProductInformation(
        "00000001",                // Manufacturer's Model serial code
        100,                       // Manufacturer's product code
        "Raymarine EV-100 Remote", // Manufacturer's Model ID
        "1.0.0.0",                 // Manufacturer's Software version code
        "1.0.0.0"                  // Manufacturer's Model version
    );

    NMEA2000.SetDeviceInformation(
        1,   // Unique number (21 bit)
        140, // Device function (Steering and Control)
        120, // Device class (Display)
        1851 // Manufacturer code (Raymarine)
    );

    NMEA2000.SetInstallationDescription1("Raymarine EV-100");
    NMEA2000.SetInstallationDescription2("ESP32 Remote Control");
    NMEA2000.SetMode(tNMEA2000::N2km_NodeOnly);

    Ready = NMEA2000.Open();
}

bool RaymarinePilot::isReady() const
{
    return Ready;
}

void RaymarinePilot::setMode(PilotModes mode)
{
    tN2kMsg N2kMsg;
    N2kMsg.SetPGN(126208UL);
    N2kMsg.Priority = 3;
    N2kMsg.Destination = PILOT_SOURCE_ADDRESS;
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
    NMEA2000.SendMsg(N2kMsg);
}

void RaymarinePilot::setObservedState(PilotState state)
{
    ObservedState = state;
}

AutopilotInterface::PilotState RaymarinePilot::getState() const
{
    return ObservedState;
}

void RaymarinePilot::turn(TurnCommands command)
{
    tN2kMsg N2kMsg;
    uint16_t keyCommand;

    switch (command)
    {
    case TURN_LEFT_TEN:
        keyCommand = MINUS_10;
        break;
    case TURN_RIGHT_TEN:
        keyCommand = PLUS_10;
        break;
    default:
        return; // Ignore other commands for now
    }

    byte commandByte0, commandByte1;
    commandByte0 = keyCommand >> 8;
    commandByte1 = keyCommand & 0xff;

    N2kMsg.SetPGN(126720UL);
    N2kMsg.Priority = 7;
    N2kMsg.Destination = PILOT_SOURCE_ADDRESS;

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
    NMEA2000.SendMsg(N2kMsg);
}

void RaymarinePilot::update()
{
    NMEA2000.ParseMessages();
}