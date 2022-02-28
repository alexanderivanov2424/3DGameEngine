#include "system.h"

System::System(){

}

void System::addComponent(std::shared_ptr<Component> c){
    components.append(c);
}

bool System::removeComponent(std::shared_ptr<Component> c){
    return components.removeOne(c);
}

void System::tick(float seconds){}
void System::draw(Graphics *g){}

void System::mousePressEvent(QMouseEvent *event){}
void System::mouseMoveEvent(QMouseEvent *event){}
void System::mouseReleaseEvent(QMouseEvent *event){}
void System::wheelEvent(QWheelEvent *event){}
void System::keyPressEvent(QKeyEvent *event){}
void System::keyRepeatEvent(QKeyEvent *event){}
void System::keyReleaseEvent(QKeyEvent *event){}
