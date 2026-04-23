#include <Arduino.h>
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"
#include "BuzzerInterface.h"
#include "PiezoActiveBuzzer.h"
#include "Button2.h"
// Create button instances
Button2 on(13);       // Pin 13 - Auto Mode
Button2 off(12);      // Pin 12 - Standby Mode
Button2 plusTen(14);  // Pin 14 - Starboard 10°
Button2 minusTen(26); // Pin 26 - Port 10°

// Buzzer instance (using interface for flexibility)
BuzzerInterface *buzzer = new PiezoActiveBuzzer(4);

// Global pilot instance (will be initialized in setup())
AutopilotInterface *pilot = nullptr;

// Handler functions
void offHandler(Button2 &btn)
{
  buzzer->beep();
  pilot->setMode(AutopilotInterface::MODE_STANDBY);
}

void onHandler(Button2 &btn)
{
  buzzer->beep();
  pilot->setMode(AutopilotInterface::MODE_AUTO);
}

void plusTenHandler(Button2 &btn)
{
  buzzer->beep();
  pilot->turn(AutopilotInterface::TURN_RIGHT_TEN);
}

void minusTenHandler(Button2 &btn)
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
  on.setTapHandler(onHandler);
  off.setTapHandler(offHandler);
  plusTen.setTapHandler(plusTenHandler);
  minusTen.setTapHandler(minusTenHandler);
}

void loop()
{
  on.loop();
  off.loop();
  plusTen.loop();
  minusTen.loop();
  pilot->update();
  // Small delay to save CPU cycles
  delay(40);
}