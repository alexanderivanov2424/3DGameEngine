#include "inputsystem.h"


#include "engine/component.h"

InputSystem::InputSystem(){

}

SystemFlag InputSystem::systemFlag(){
    return INPUT_SYSTEM;
}

void InputSystem::mousePressEvent(QMouseEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->mousePressEvent(event);
    }
}

void InputSystem::mouseMoveEvent(QMouseEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->mouseMoveEvent(event);
    }
}

void InputSystem::mouseReleaseEvent(QMouseEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->mouseReleaseEvent(event);
    }
}

void InputSystem::wheelEvent(QWheelEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->wheelEvent(event);
    }
}

void InputSystem::keyPressEvent(QKeyEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->keyPressEvent(event);
    }
}

void InputSystem::keyRepeatEvent(QKeyEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->keyRepeatEvent(event);
    }
}

void InputSystem::keyReleaseEvent(QKeyEvent *event){
    for(std::shared_ptr<Component> comp : components){
        comp->keyReleaseEvent(event);
    }
}


