#include "application.h"

class Screen;

Application::Application(){
//    m_camera = std::make_shared<Camera>();
    currentScreenTag = "";
    currentScreen = nullptr;
}

Application::~Application(){
}

void Application::setCurrentScreen(QString screenTag){
    currentScreenTag = screenTag;
    currentScreen = getCurrentScreen();
}

Screen* Application::getCurrentScreen(){
    return screens.value(currentScreenTag);
}

void Application::tick(float seconds){
    currentScreen->tick(seconds);
}

void Application::draw(Graphics *g){
    currentScreen->draw(g);
}

void Application::mousePressEvent(QMouseEvent *event){
    currentScreen->mousePressEvent(event);
}

void Application::mouseMoveEvent(QMouseEvent *event){
    currentScreen->mouseMoveEvent(event);
}

void Application::mouseReleaseEvent(QMouseEvent *event){
    currentScreen->mouseReleaseEvent(event);
}

void Application::wheelEvent(QWheelEvent *event){
    currentScreen->wheelEvent(event);
}

void Application::keyPressEvent(QKeyEvent *event){
    currentScreen->keyPressEvent(event);
}

void Application::keyRepeatEvent(QKeyEvent *event){
    currentScreen->keyRepeatEvent(event);
}

void Application::keyReleaseEvent(QKeyEvent *event){
    currentScreen->keyReleaseEvent(event);
}

void Application::resize(int w, int h){
    currentScreen->resize(w, h);
}
