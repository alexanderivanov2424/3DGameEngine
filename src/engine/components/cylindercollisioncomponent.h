#ifndef CYLINDERCOLLISIONCOMPONENT_H
#define CYLINDERCOLLISIONCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "engine/component.h"

using f_callback = void(*)(std::shared_ptr<GameObject>); //int(*)(int)


class CylinderCollisionComponent : public Component{
public:
    CylinderCollisionComponent(std::shared_ptr<GameObject> gameObject,
                               glm::vec3 offset,
                               float radius,
                               float height,
                               bool stationary,
                               f_callback callback);

    CylinderCollisionComponent(std::shared_ptr<GameObject> gameObject,
                               float radius,
                               float height,
                               bool stationary,
                               f_callback callback);

    SystemFlag requiresSystems() override { return COLLISION_SYSTEM;}

    glm::vec3 getAbsolutePosition();

    void applyMTV(glm::vec3 mtv);

public:
    f_callback callback;
    float radius;
    float height;
    bool stationary;

private:
    glm::vec3 offset;

};

#endif // CYLINDERCOLLISIONCOMPONENT_H
