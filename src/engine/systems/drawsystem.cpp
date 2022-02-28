#include "drawsystem.h"

#include "engine/component.h"


DrawSystem::DrawSystem()  : System() {

}

SystemFlag DrawSystem::systemFlag(){
    return DRAW_SYSTEM;
}


void DrawSystem::draw(Graphics *g){
    for(std::shared_ptr<Component> comp : components){
        comp->draw(g);
    }
}
