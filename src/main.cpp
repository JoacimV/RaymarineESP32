#include <Arduino.h>
#include "Button.h"
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"

// Create button instances
Button on(13);       // Pin 13 - Auto Mode
Button off(12);      // Pin 12 - Standby Mode
Button minusTen(14); // Pin 14 - Starboard 10°
Button plusTen(26);  // Pin 26 - Port 10°

// Global pilot instance (will be initialized in setup())
AutopilotInterface *pilot = nullptr;

// Handler functions
void offHandler()
{
  pilot->setMode(AutopilotInterface::MODE_STANDBY);
}

void onHandler()
{
  pilot->setMode(AutopilotInterface::MODE_AUTO);
}

void plusTenHandler()
{
  pilot->turn(AutopilotInterface::TURN_RIGHT_TEN);
}

void minusTenHandler()
{
  pilot->turn(AutopilotInterface::TURN_LEFT_TEN);
}

// Setup function - now AFTER handler definitions
void setup()
{
  Serial.begin(115200);

  // Initialize NMEA2000 for Raymarine communication
  if (RaymarinePilot::initializeNMEA2000())
  {
    Serial.println("✅ Raymarine ESP32 Remote Ready!");
  }
  else
  {
    Serial.println("❌ NMEA2000 failed to initialize");
  }

  pilot = new RaymarinePilot();
  // Setup buttons with handlers
  on.setup(onHandler);
  off.setup(offHandler);
  plusTen.setup(plusTenHandler);
  minusTen.setup(minusTenHandler);
}

void loop()
{
  pilot->update();
  delay(40);
}