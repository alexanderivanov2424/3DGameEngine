#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"


class TickSystem : public System {
public:
    TickSystem();

    SystemFlag systemFlag() override;

    void tick(float seconds) override;
};

#endif // TICKSYSTEM_H
