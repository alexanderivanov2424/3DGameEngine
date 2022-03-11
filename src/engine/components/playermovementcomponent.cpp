#include "playermovementcomponent.h"

#include <QDebug>

#include "engine/gameobject.h"
#include "engine/gameworld.h"
#include "engine/graphics/Camera.h"

#include "engine/components/transformcomponent.h"

PlayerMovementComponent::PlayerMovementComponent(std::shared_ptr<GameObject> g) : Component(g){

}

void PlayerMovementComponent::tick(float seconds){
    std::shared_ptr<QMap<int,bool>> keyMap = this->gameObject->gameWorld->getKeyMap();
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    std::shared_ptr<Camera> camera = this->gameObject->gameWorld->getCamera();


    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    dir *= .2f;
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);


    if((*keyMap)[Qt::Key_W]) transform->transform += dir;
    if((*keyMap)[Qt::Key_S]) transform->transform += -dir;
    if((*keyMap)[Qt::Key_A]) transform->transform += perp;
    if((*keyMap)[Qt::Key_D]) transform->transform += -perp;

    transform->transform[1] += playerYVel * seconds;
    playerYVel += -20 * seconds;

    if(transform->transform[1] <= 0){
        transform->transform[1] = 0;
        playerYVel = 0;
        onGround = true;
    }

    if((*keyMap)[Qt::Key_Space] && onGround){
        transform->transform[1] += .001f;
        playerYVel = 10;
        onGround = false;
    }
}

void PlayerMovementComponent::hitGround(){
    onGround = true;
    playerYVel = 0;
}
