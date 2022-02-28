#include "screen.h"

#include "engine/application.h"
#include "engine/gameworld.h"

#include<QDebug>
#include <QKeyEvent>

Screen::Screen(std::shared_ptr<Application> application){
    this->application = application;
    gameWorld = std::make_shared<GameWorld>();
}

void Screen::setParentApplication(std::shared_ptr<Application> app){
    application = app;
}

void Screen::tick(float seconds){
    gameWorld->tick(seconds);
}

void Screen::draw(Graphics *g){
    gameWorld->draw(g);
}

void Screen::mousePressEvent(QMouseEvent *event){
    gameWorld->mousePressEvent(event);
}

void Screen::mouseMoveEvent(QMouseEvent *event){
    gameWorld->mouseMoveEvent(event);
}

void Screen::mouseReleaseEvent(QMouseEvent *event){
    gameWorld->mouseReleaseEvent(event);
}

void Screen::wheelEvent(QWheelEvent *event){
    gameWorld->wheelEvent(event);
}

void Screen::keyPressEvent(QKeyEvent *event){
    gameWorld->keyPressEvent(event);
    keyMap[event->key()] = true;
}

void Screen::keyRepeatEvent(QKeyEvent *event){
    gameWorld->keyRepeatEvent(event);
}

void Screen::keyReleaseEvent(QKeyEvent *event){
    gameWorld->keyReleaseEvent(event);
    keyMap[event->key()] = false;
}

void Screen::resize(int w, int h){
    camera->setScreenSize(glm::vec2(w, h));
}

