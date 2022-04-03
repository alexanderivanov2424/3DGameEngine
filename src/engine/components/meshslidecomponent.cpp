#include "meshslidecomponent.h"

#include <QDebug>

#include "engine/gameobject.h"
#include "engine/gameworld.h"
#include "engine/graphics/Camera.h"

#include "engine/components/transformcomponent.h"
#include "engine/systems/collisionUtils/meshcollision.h"

#include "engine/shapes/mesh.h"
#include "engine/shapes/ellipsoid.h"

#include "engine/graphics/Graphics.h"

MeshSlideComponent::MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<Mesh> mesh) : Component(g){
    ellipsoid = std::make_shared<Ellipsoid>(glm::vec3(0,0,0), glm::vec3(1,1,1));
    this->mesh = mesh;
}

MeshSlideComponent::MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipsoid) : Component(g){
    this->ellipsoid = ellipsoid;
    this->mesh = mesh;
}

void MeshSlideComponent::tick(float seconds){
    std::shared_ptr<QMap<int,bool>> keyMap = this->gameObject->gameWorld->getKeyMap();
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    std::shared_ptr<Camera> camera = this->gameObject->gameWorld->getCamera();

    float speed = .1f;

    glm::vec3 next_pos = transform->transform;

    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    dir *= speed;
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if((*keyMap)[Qt::Key_W]) next_pos += dir;
    if((*keyMap)[Qt::Key_S]) next_pos += -dir;
    if((*keyMap)[Qt::Key_A]) next_pos += perp;
    if((*keyMap)[Qt::Key_D]) next_pos += -perp;

    if(DEBUG){
        if((*keyMap)[Qt::Key_Shift]) next_pos += -glm::vec3(0,speed,0);
        if((*keyMap)[Qt::Key_Space]) next_pos += glm::vec3(0,speed,0);

        if((*keyMap)[Qt::Key_Q]){
            root = transform->transform;
        }

        ellipsoid->m_pos = transform->transform;
        ellipsoid->m_pos = root;
        Collision c = MeshCollision::collide(mesh, ellipsoid, next_pos);

        transform->transform = next_pos;
        bounce = c.contact;
    } else {
        if((*keyMap)[Qt::Key_Space] && onGround){
            next_pos[1] += .001f;
            playerYVel = 10;
            onGround = false;
        }

        playerYVel += -20 * seconds;
        next_pos[1] += playerYVel * seconds;


        if(next_pos[1] <= -5){
            next_pos[1] = -5;
            playerYVel = 0;
            onGround = true;
        }

    ellipsoid->m_pos = transform->transform;
    Collision c = MeshCollision::slide(mesh, ellipsoid, next_pos);

    if(c.isCollision){
        onGround = true;
        next_pos = c.contact;
        playerYVel = 0;
    }

    transform->transform = next_pos;

    }
}

void MeshSlideComponent::draw(Graphics *g){
    if(DEBUG){
        std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
        g->clearTransform();
        g->setMaterial("blue");
        g->translate(root);
        g->scale(ellipsoid->m_radii*2.0f);
        g->drawShape("sphere");

        g->clearTransform();
        g->setMaterial("red");
        g->translate(transform->transform);
        g->scale(ellipsoid->m_radii*2.0f);
        g->drawShape("sphere");

        g->clearTransform();
        g->setMaterial("green");
        g->translate(bounce);
        g->scale(ellipsoid->m_radii*2.0f);
        g->drawShape("sphere");
    }
}
