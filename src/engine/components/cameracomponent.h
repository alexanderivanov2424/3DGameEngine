#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

#include "engine/component.h"

class GameObject;

class CameraComponent : public Component{
public:
    CameraComponent(std::shared_ptr<GameObject> gameObject);

    SystemFlag requiresSystems() override { return TICK_SYSTEM | INPUT_SYSTEM;}

    void tick(float seconds) override;

    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    float zoom = 0;
};

#endif // CAMERACOMPONENT_H
