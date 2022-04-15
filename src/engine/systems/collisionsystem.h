#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"


class CollisionSystem : public System {
public:
    CollisionSystem();

    SystemFlag systemFlag() override;

    void tick(float seconds) override;

};

#endif // COLLISIONSYSTEM_H
