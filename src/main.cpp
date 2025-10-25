#include <Arduino.h>
#include "Button.h"
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"
#include "BuzzerInterface.h"
#include "PiezoActiveBuzzer.h"

// Create button instances
Button on(13);       // Pin 13 - Auto Mode
Button off(12);      // Pin 12 - Standby Mode
Button minusTen(14); // Pin 14 - Starboard 10°
Button plusTen(26);  // Pin 26 - Port 10°

// Buzzer instance (using interface for flexibility)
BuzzerInterface *buzzer = new PiezoActiveBuzzer(4);

// Global pilot instance (will be initialized in setup())
AutopilotInterface *pilot = nullptr;

// Handler functions
void offHandler()
{
  buzzer->beep();
  pilot->setMode(AutopilotInterface::MODE_STANDBY);
}

void onHandler()
{
  buzzer->beep();
  pilot->setMode(AutopilotInterface::MODE_AUTO);
}

void plusTenHandler()
{
  buzzer->beep();
  pilot->turn(AutopilotInterface::TURN_RIGHT_TEN);
}

void minusTenHandler()
{
  buzzer->beep();
  pilot->turn(AutopilotInterface::TURN_LEFT_TEN);
}

// Setup function - now AFTER handler definitions
void setup()
{
  Serial.begin(115200);

  // Initialize buzzer
  buzzer->begin();

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
  // Small delay to save CPU cycles
  delay(40);
}