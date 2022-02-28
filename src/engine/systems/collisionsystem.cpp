#include "collisionsystem.h"

#include "engine/component.h"


CollisionSystem::CollisionSystem() : System() {

}

SystemFlag CollisionSystem::systemFlag(){
    return DRAW_SYSTEM;
}


void CollisionSystem::tick(float seconds){
//    for(std::shared_ptr<Component> comp : components){
//        comp->tick(seconds);
//    }
}
