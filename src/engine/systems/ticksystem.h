#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"


class TickSystem : public System {
public:
    TickSystem();

    SystemFlag systemFlag();

    void tick(float seconds);
};

#endif // TICKSYSTEM_H
