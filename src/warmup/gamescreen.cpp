#include "gamescreen.h"

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

void warmup_callback(std::shared_ptr<GameObject> g){
    g->getComponent<PlayerMovementComponent>()->hitGround();
}

void warmup_endGame(std::shared_ptr<GameObject> g){
    g->gameWorld->screen->application->setCurrentScreen("endScreen");
}

void warmup_makePlatform(std::shared_ptr<GameWorld> gameWorld, glm::vec3 location, float height){
    std::shared_ptr<GameObject> platform = std::make_shared<GameObject>(gameWorld);
    platform->addComponent<TransformComponent>(std::make_shared<TransformComponent>(platform, location));
    platform->addComponent<CylinderComponent>(std::make_shared<CylinderComponent>(platform, 4, height));
    platform->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(platform, 4, height, true, nullptr));
    gameWorld->addGameObject(platform);
}

void warmup_makeWinToken(std::shared_ptr<GameWorld> gameWorld, glm::vec3 location){
    std::shared_ptr<GameObject> platform = std::make_shared<GameObject>(gameWorld);
    platform->addComponent<TransformComponent>(std::make_shared<TransformComponent>(platform, location));
    platform->addComponent<CylinderComponent>(std::make_shared<CylinderComponent>(platform, .5, 1, "token"));
    platform->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(platform, .5, 1, true, &warmup_endGame));
    gameWorld->addGameObject(platform);
}

GameScreen::GameScreen(std::shared_ptr<Application> application) : Screen(application){
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
    player->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(player, 1, 3, false, &warmup_callback));
    gameWorld->addGameObject(player);

    std::shared_ptr<GameObject> platform = std::make_shared<GameObject>(gameWorld);
    platform->addComponent<TransformComponent>(std::make_shared<TransformComponent>(platform, glm::vec3(20,0,10)));
    platform->addComponent<CylinderComponent>(std::make_shared<CylinderComponent>(platform, 1, 2));
    platform->addComponent<CylinderCollisionComponent>(std::make_shared<CylinderCollisionComponent>(platform, 1, 2, false, nullptr));
    gameWorld->addGameObject(platform);


    warmup_makePlatform(gameWorld, glm::vec3(10,0,10), 2);
    warmup_makePlatform(gameWorld, glm::vec3(10,0,20), 3);
    warmup_makePlatform(gameWorld, glm::vec3(10,0,30), 4);
    warmup_makePlatform(gameWorld, glm::vec3(20,0,40), 5);

    warmup_makeWinToken(gameWorld, glm::vec3(20,6,40));

}


void GameScreen::onSwitch(){
    QApplication::setOverrideCursor(Qt::BlankCursor);
    player->getComponent<TransformComponent>()->transform = glm::vec3(0,0,0);
}


void GameScreen::draw(Graphics *g){
    Screen::draw(g);
    int w = application->width;
    int h = application->height;
    camera->setScreenSize(glm::vec2(w, h));
    g->setCamera(camera);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            g->clearTransform();
            g->scale(20);
            g->translate(glm::vec3(i,0,j));
            g->scale(19.0/20.0);
            g->setMaterial("grass");
            g->drawShape("quad");
        }
    }
}

void GameScreen::keyPressEvent(QKeyEvent *event){
    Screen::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape) application->setCurrentScreen("menuScreen");
}

