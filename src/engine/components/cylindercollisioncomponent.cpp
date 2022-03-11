#include "cylindercollisioncomponent.h"


#include "engine/gameobject.h"

#include "engine/components/transformcomponent.h"

CylinderCollisionComponent::CylinderCollisionComponent(
        std::shared_ptr<GameObject> g,
        glm::vec3 offset,
        float radius,
        float height,
        bool stationary,
        f_callback callback) : Component(g){

    this->offset = offset;
    this->radius = radius;
    this->height = height;
    this->stationary = stationary;
    this->callback = callback;
}

CylinderCollisionComponent::CylinderCollisionComponent(
        std::shared_ptr<GameObject> g,
        float radius,
        float height,
        bool stationary,
        f_callback callback) : Component(g){

    this->offset = glm::vec3(0,0,0);
    this->radius = radius;
    this->height = height;
    this->stationary = stationary;
    this->callback = callback;
}

glm::vec3 CylinderCollisionComponent::getAbsolutePosition(){
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    return offset + transform->transform;
}

void CylinderCollisionComponent::applyMTV(glm::vec3 mtv){
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    transform->transform += mtv;
}
