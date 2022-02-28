#include "ticksystem.h"

#include "engine/component.h"

TickSystem::TickSystem() : System() {

}

SystemFlag TickSystem::systemFlag(){
    return TICK_SYSTEM;
}


void TickSystem::tick(float seconds){
    for(std::shared_ptr<Component> comp : components){
        comp->tick(seconds);
    }
}
