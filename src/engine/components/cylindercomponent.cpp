#include "cylindercomponent.h"

#include <QDebug>

#include "engine/graphics/Graphics.h"

#include "engine/gameobject.h"
#include "engine/components/transformcomponent.h"


CylinderComponent::CylinderComponent(std::shared_ptr<GameObject> g,
                                     float radius,
                                     float height) : Component(g){
    this->radius = radius;
    this->height = height;
}

CylinderComponent::CylinderComponent(std::shared_ptr<GameObject> g,
                                     float radius,
                                     float height,
                                     QString texture) : Component(g){
    this->radius = radius;
    this->height = height;
    this->texture = texture;
}


void CylinderComponent::draw(Graphics *g){
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    g->clearTransform();
    if(texture == ""){
        g->setDefaultMaterial();
    } else {
        g->setMaterial(texture.toStdString());
    }
    g->translate(transform->transform);
    g->scale(glm::vec3(2*radius,height,2*radius));
    g->drawShape("cylinder");
}
