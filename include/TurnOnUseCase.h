#ifndef TURN_ON_USE_CASE_H
#define TURN_ON_USE_CASE_H

#include "AutopilotInterface.h"
#include "UsecaseInterface.h"
/**
 * Use case for turning on the autopilot (setting it to AUTO mode)
 */
class TurnOnUseCase : public UseCase<void, void>
{
private:
    AutopilotInterface *autopilot;

public:
    // Constructor that takes autopilot interface
    TurnOnUseCase(AutopilotInterface *autopilotInterface);

    // Execute the use case
    void apply() override;
};

#endif // TURN_ON_USE_CASE_H