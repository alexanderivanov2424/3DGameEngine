#include "transformcomponent.h"

TransformComponent::TransformComponent(std::shared_ptr<GameObject> g) : Component(g){
    transform = glm::vec3(0,0,0);
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> g, glm::vec3 transform) : Component(g){
    this->transform = transform;
}
