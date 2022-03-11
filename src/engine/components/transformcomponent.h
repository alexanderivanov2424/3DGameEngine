#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "engine/component.h"

class TransformComponent : public Component{
public:
    TransformComponent(std::shared_ptr<GameObject> gameObject);

    TransformComponent(std::shared_ptr<GameObject> gameObject, glm::vec3 transform);

    SystemFlag requiresSystems() override { return NO_SYSTEM;}

public:
    glm::vec3 transform;
};

#endif // TRANSFORMCOMPONENT_H
