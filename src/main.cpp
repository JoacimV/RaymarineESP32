#include <Arduino.h>
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"
#include "MessageHandler.h"
#include "BuzzerInterface.h"
#include "PiezoActiveBuzzer.h"
#include "Button2.h"

// Create button instances
Button2 on(14);       // Pin 14 - Auto Mode
Button2 plusTen(12);  // Pin 12 - Starboard 10°
Button2 minusTen(13); // Pin 13 - Port 10°

// Buzzer instance (using interface for flexibility)
BuzzerInterface *buzzer = new PiezoActiveBuzzer(27);

// Global pilot instance (will be initialized in setup())
AutopilotInterface *pilot = nullptr;

void pilotStateUpdateHandler(AutopilotInterface::PilotState state)
{
  if (pilot != nullptr)
  {
    pilot->setObservedState(state);
  }
}

// Handler functions
void onHandler(Button2 &btn)
{
  buzzer->beep();
  AutopilotInterface::PilotState state = pilot->getState();

  // Toggle based on latest bus state; unknown defaults to AUTO.
  if (state == AutopilotInterface::STATE_AUTO)
  {
    pilot->setMode(AutopilotInterface::MODE_STANDBY);
  }
  else
  {
    pilot->setMode(AutopilotInterface::MODE_AUTO);
  }
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
  Serial.println("Starting Raymarine ESP32 Remote...");

  // Initialize buzzer
  buzzer->begin();

  pilot = new RaymarinePilot();
  if (pilot->isReady())
  {
    Serial.println("✅ Raymarine ESP32 Remote Ready!");
  }
  else
  {
    Serial.println("❌ NMEA2000 failed to initialize");
  }
  MessageHandler::SetPilotStateUpdateCallback(pilotStateUpdateHandler);

  // Setup buttons with handlers
  on.setTapHandler(onHandler);
  plusTen.setTapHandler(plusTenHandler);
  minusTen.setTapHandler(minusTenHandler);
}

void loop()
{
  on.loop();
  plusTen.loop();
  minusTen.loop();
  pilot->update();
  // Small delay to save CPU cycles
  // delay(40);
}