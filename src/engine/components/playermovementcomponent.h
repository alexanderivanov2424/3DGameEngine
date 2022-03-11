#ifndef PLAYERMOVEMENTCOMPONENT_H
#define PLAYERMOVEMENTCOMPONENT_H

#include "engine/component.h"

class PlayerMovementComponent : public Component{
public:
    PlayerMovementComponent(std::shared_ptr<GameObject> gameObject);

    SystemFlag requiresSystems() override { return TICK_SYSTEM;}

    void tick(float seconds) override;

    void hitGround();

private:
    float playerYVel = 0;
    bool onGround = false;

};

#endif // PLAYERMOVEMENTCOMPONENT_H
