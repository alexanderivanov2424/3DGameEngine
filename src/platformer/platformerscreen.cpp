#include "platformerscreen.h"

#include <QApplication>
#include <QWindow>
#include <QKeyEvent>
#include <QDebug>

#include "view.h"
#include "engine/application.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"
#include "engine/systems/inputsystem.h"

#include "engine/gameworld.h"
#include "engine/gameobject.h"
#include "engine/component.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/playermovementcomponent.h"
#include "engine/components/cameracomponent.h"
#include "engine/components/cylindercomponent.h"
#include "engine/components/cylindercollisioncomponent.h"


PlatformerScreen::PlatformerScreen(std::shared_ptr<Application> application) : Screen(application){
    tickSystem = std::make_shared<TickSystem>();
    drawSystem = std::make_shared<DrawSystem>();
    collisionSystem = std::make_shared<CollisionSystem>();
    inputSystem = std::make_shared<InputSystem>();

    this->gameWorld->addSystem(tickSystem);
    this->gameWorld->addSystem(drawSystem);
    this->gameWorld->addSystem(collisionSystem);
    this->gameWorld->addSystem(inputSystem);

    player = std::make_shared<GameObject>(gameWorld);
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player));
    player->addComponent<PlayerMovementComponent>(std::make_shared<PlayerMovementComponent>(player));
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(player));
    player->addComponent<CylinderComponent>(std::make_shared<CylinderComponent>(player, 1, 3, "player"));
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(player, 1, 3, false, nullptr));
    gameWorld->addGameObject(player);

    std::shared_ptr<GameObject> platform = std::make_shared<GameObject>(gameWorld);
    platform->addComponent<TransformComponent>(std::make_shared<TransformComponent>(platform, glm::vec3(20,0,10)));
    platform->addComponent<CylinderComponent>(std::make_shared<CylinderComponent>(platform, 1, 2));
    platform->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(platform, 1, 2, false, nullptr));
    gameWorld->addGameObject(platform);


}


void PlatformerScreen::onSwitch(){
    QApplication::setOverrideCursor(Qt::BlankCursor);
    player->getComponent<TransformComponent>()->transform = glm::vec3(0,0,0);
}


void PlatformerScreen::draw(Graphics *g){
    Screen::draw(g);
    int w = application->width;
    int h = application->height;
    camera->setScreenSize(glm::vec2(w, h));
    g->setCamera(camera);

//    for(int i = 0; i<10; i++){
//        for(int j = 0; j<10; j++){
//            g->clearTransform();
//            g->scale(20);
//            g->translate(glm::vec3(i,0,j));
//            g->setMaterial("grass");
//            g->drawShape("quad");
//        }
//    }

    g->clearTransform();
    g->translate(glm::vec3(0,0,0));
    //g->setMaterial("default");
    g->drawShape("mesh");
}

void PlatformerScreen::keyPressEvent(QKeyEvent *event){
    Screen::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape) QApplication::quit();
}

