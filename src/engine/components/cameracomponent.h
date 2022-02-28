#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

#include "engine/component.h"

class GameObject;

class CameraComponent : Component{
public:
    CameraComponent(std::shared_ptr<GameObject> g);
    SystemFlag requiresSystems(){ return TICK_SYSTEM;}

    void tick(float seconds) override;
};

#endif // CAMERACOMPONENT_H
