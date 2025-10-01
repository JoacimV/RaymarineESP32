#include <Arduino.h>
#include "Button.h"
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"
#include "MessageHandler.h"

// NMEA2000 Libraries
#define N2k_SPI_CS_PIN 5
#include <NMEA2000_mcp.h>
#include <N2kMessages.h>

tNMEA2000_mcp NMEA2000(N2k_SPI_CS_PIN, MCP_8MHz);

// Create button instances
Button on(13);       // Pin 13 - Auto Mode
Button off(12);      // Pin 12 - Standby Mode
Button minusTen(14); // Pin 14 - Starboard 10°
Button plusTen(26);  // Pin 26 - Port 10°

/**
 * @brief Setup NMEA2000 with Raymarine device information
 * This function configures the NMEA2000 interface with the necessary
 * device information for a Raymarine EV-100 autopilot remote control.
 * @return true if initialization was successful.
 */
bool setupNMEA2000()
{
  // Configure NMEA2000 buffers
  NMEA2000.SetN2kCANReceiveFrameBufSize(150);
  NMEA2000.SetN2kCANMsgBufSize(10);
  NMEA2000.SetMsgHandler(MessageHandler::HandleNMEA2000Msg);

  // Set device information
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

  // Open NMEA2000 interface and return the result
  return NMEA2000.Open();
}

void setup()
{
  Serial.begin(115200);
  if (setupNMEA2000())
  {
    // TODO: Could turn on a LED indicator here on successful initialization
    Serial.println("✅ Raymarine ESP32 Remote Ready!");
  }
  else
  {
    Serial.println("❌ NMEA2000 failed to initialize");
  }

  AutopilotInterface *pilot = new RaymarinePilot(NMEA2000);
  // If you want to create new implementations for other autopilot brands, you can copy the RaymarinePilot class and modify it accordingly.
  // Then, you can instantiate your new class here.
  // AutopilotInterface *pilot = new GarminPilot(NMEA2000);
  // AutopilotInterface *pilot = new SimradPilot(NMEA2000);
  // AutopilotInterface *pilot = new B&G(NMEA2000);

  // Setup buttons with callbacks
  on.setup(pilot->on());
  off.setup(pilot->standby());
  plusTen.setup(pilot->plus10());
  minusTen.setup(pilot->minus10());
}

void loop()
{
  NMEA2000.ParseMessages();
  delay(50);
}