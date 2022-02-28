#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

class CollisionSystem : public System {
public:
    CollisionSystem();

    SystemFlag systemFlag();

    void tick(float seconds);
};

#endif // COLLISIONSYSTEM_H
