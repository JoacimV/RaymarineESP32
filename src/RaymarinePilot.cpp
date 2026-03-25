#include "RaymarinePilot.h"
#include "MessageHandler.h"
#include <NMEA2000_mcp.h>
#include <ActisenseReader.h>

tActisenseReader ActisenseReader;
#define N2k_SPI_CS_PIN 5

// Define READ_STREAM to port, where you write data from PC e.g. with NMEA Simulator.
#define READ_STREAM Serial
// Define ForwardStream to port, what you listen on PC side. On Arduino Due you can use e.g. SerialUSB
#define FORWARD_STREAM Serial

tNMEA2000_mcp NMEA2000(N2k_SPI_CS_PIN, MCP_8MHz);
Stream *ReadStream = &READ_STREAM;
Stream *ForwardStream = &FORWARD_STREAM;

RaymarinePilot::RaymarinePilot() : AutopilotInterface() {}

bool RaymarinePilot::initializeNMEA2000()
{
    // Configure NMEA2000 buffers for Raymarine communication
    NMEA2000.SetN2kCANReceiveFrameBufSize(200);
    NMEA2000.SetN2kCANMsgBufSize(20);
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
    if (ReadStream != ForwardStream)
        READ_STREAM.begin(115200);
    FORWARD_STREAM.begin(115200);
    NMEA2000.SetForwardStream(ForwardStream);
    NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode);

    ActisenseReader.SetReadStream(ReadStream);
    ActisenseReader.SetDefaultSource(75);
    ActisenseReader.SetMsgHandler([](const tN2kMsg &msg)
                                  { NMEA2000.SendMsg(msg); });
    // Open NMEA2000 interface and return the result
    if (ReadStream == ForwardStream)
        NMEA2000.SetForwardOwnMessages(false); // If streams are same, do not echo own messages.
    return NMEA2000.Open();
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
    ActisenseReader.ParseMessages();
}