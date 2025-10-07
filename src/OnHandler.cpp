#include "OnHandler.h"
#include <Arduino.h>
#include "AutopilotInterface.h"
#include "RaymarinePilot.h"

AutopilotInterface *OnHandler::autopilot = nullptr;

OnHandler::OnHandler(tNMEA2000_mcp &nmea2000)
{
    if (autopilot == nullptr)
    {
        autopilot = new RaymarinePilot(nmea2000);
    }
}

void OnHandler::execute()
{
    autopilot->SendSetMode(AutopilotInterface::MODE_AUTO);
}