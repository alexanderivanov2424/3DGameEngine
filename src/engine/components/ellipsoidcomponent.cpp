#include "ellipsoidcomponent.h"

#include "cylindercomponent.h"

#include <QDebug>

#include "engine/graphics/Graphics.h"

#include "engine/gameobject.h"
#include "engine/components/transformcomponent.h"

#include "engine/shapes/ellipsoid.h"


EllipsoidComponent::EllipsoidComponent(std::shared_ptr<GameObject> g, std::shared_ptr<Ellipsoid> ellipsoid) : Component(g){
    this->ellipsoid = ellipsoid;
}

EllipsoidComponent::EllipsoidComponent(std::shared_ptr<GameObject> g,
                                       std::shared_ptr<Ellipsoid> ellipsoid,
                                       QString texture) : Component(g){
    this->ellipsoid = ellipsoid;
    this->texture = texture;
}


void EllipsoidComponent::draw(Graphics *g){
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    g->clearTransform();
    if(texture == ""){
        g->setDefaultMaterial();
    } else {
        g->setMaterial(texture.toStdString());
    }

    g->translate(transform->transform);
    g->scale(ellipsoid->m_radii*2.0f);
    g->drawShape("sphere");
}
