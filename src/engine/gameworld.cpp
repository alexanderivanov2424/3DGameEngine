#include "gameworld.h"



#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"

#include "engine/gameobject.h"
#include "engine/component.h"
#include "engine/util/TypeMap.h"

GameWorld::GameWorld(){

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

void GameWorld::addSystem(std::shared_ptr<System> sys){
    systems.append(sys);
}

bool GameWorld::removeSystem(std::shared_ptr<System> sys){
    systems.removeOne(sys);
}

void GameWorld::tick(float seconds){
    for(std::shared_ptr<System> sys : systems){
        if(TICK_SYSTEM & sys->systemFlag()){
            sys->tick(seconds);
        }
    }
}

void GameWorld::draw(Graphics *g){
    for(std::shared_ptr<System> sys : systems){
        if(DRAW_SYSTEM & sys->systemFlag()){
            sys->draw(g);
        }
    }
}

void GameWorld::mousePressEvent(QMouseEvent *event){}
void GameWorld::mouseMoveEvent(QMouseEvent *event){}
void GameWorld::mouseReleaseEvent(QMouseEvent *event){}
void GameWorld::wheelEvent(QWheelEvent *event){}
void GameWorld::keyPressEvent(QKeyEvent *event){}
void GameWorld::keyRepeatEvent(QKeyEvent *event){}
void GameWorld::keyReleaseEvent(QKeyEvent *event){}
