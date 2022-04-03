#include "gameworld.h"

#include <QDebug>

#include "engine/screen.h"

#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"

#include "engine/gameobject.h"
#include "engine/component.h"
#include "engine/util/TypeMap.h"

#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"
#include "engine/systems/inputsystem.h"

GameWorld::GameWorld(std::shared_ptr<Screen> screen){
    this->screen = screen;

    tickSystem = std::make_shared<TickSystem>();
    drawSystem = std::make_shared<DrawSystem>();
    collisionSystem = std::make_shared<CollisionSystem>();
    inputSystem = std::make_shared<InputSystem>();

    systems.append(tickSystem);
    systems.append(drawSystem);
    systems.append(collisionSystem);
    systems.append(inputSystem);
}

void GameWorld::addGameObject(std::shared_ptr<GameObject> g){
    gameObjects.append(g);
    for(std::shared_ptr<System> sys : systems){
        TypeMap<std::shared_ptr<Component>>::iterator it;
        for(it = g->begin(); it != g->end(); it++){
            if(it->second->requiresSystems() & sys->systemFlag()){
                sys->addComponent(it->second);
            }
        }
    }
}

bool GameWorld::removeGameObject(std::shared_ptr<GameObject> g){
    bool removed = gameObjects.removeOne(g);
    for(std::shared_ptr<System> sys : systems){
        TypeMap<std::shared_ptr<Component>>::iterator it;
        for(it = g->begin(); it != g->end(); it++){
            if(it->second->requiresSystems() & sys->systemFlag()){
                sys->removeComponent(it->second);
            }
        }
    }
    return removed;
}

std::shared_ptr<QMap<int, bool>> GameWorld::getKeyMap(){
    return screen->keyMap;
}

std::shared_ptr<Camera> GameWorld::getCamera(){
    return screen->camera;
}

void GameWorld::tick(float seconds){
    for(std::shared_ptr<System> sys : systems){
        if(TICK_SYSTEM & sys->systemFlag()){
            sys->tick(seconds);
        }
    }

    for(std::shared_ptr<System> sys : systems){
        if(COLLISION_SYSTEM & sys->systemFlag()){
            sys->tick(seconds);
        }
    }
}

void GameWorld::draw(Graphics *g){
    QList<std::shared_ptr<System>>::iterator sys;
    for(sys = systems.begin(); sys != systems.end(); sys++){
        if(DRAW_SYSTEM & (*sys)->systemFlag()){
            (*sys)->draw(g);
        }
    }
}

void GameWorld::mousePressEvent(QMouseEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->mousePressEvent(event);
        }
    }
}

void GameWorld::mouseMoveEvent(QMouseEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->mouseMoveEvent(event);
        }
    }
}

void GameWorld::mouseReleaseEvent(QMouseEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->mouseReleaseEvent(event);
        }
    }
}

void GameWorld::wheelEvent(QWheelEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->wheelEvent(event);
        }
    }
}

void GameWorld::keyPressEvent(QKeyEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->keyPressEvent(event);
        }
    }
}

void GameWorld::keyRepeatEvent(QKeyEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->keyRepeatEvent(event);
        }
    }
}

void GameWorld::keyReleaseEvent(QKeyEvent *event){
    for(std::shared_ptr<System> sys : systems){
        if(INPUT_SYSTEM & sys->systemFlag()){
            sys->keyReleaseEvent(event);
        }
    }
}
