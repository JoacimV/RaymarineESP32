#include "TurnOnUseCase.h"
// Constructor implementation
TurnOnUseCase::TurnOnUseCase(AutopilotInterface *autopilotInterface)
    : autopilot(autopilotInterface)
{
}

// Apply method implementation
void TurnOnUseCase::apply()
{
    if (autopilot != nullptr)
    {
        autopilot->SendSetMode(AutopilotInterface::MODE_AUTO);
    }
}
