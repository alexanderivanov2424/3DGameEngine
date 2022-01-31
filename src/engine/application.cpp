#include "application.h"

class Screen;

Application::Application(){
    m_camera = std::make_shared<Camera>();
    currentScreen = "";
}

Application::~Application(){
}

void Application::setCurrentScreen(std::string screenTag){
    currentScreen = screenTag;
}

Screen* Application::getCurrentScreen(){
    return screens.find(currentScreen)->second;
}

void Application::tick(float seconds){
}

void Application::draw(Graphics *g){
}

void mousePressEvent(QMouseEvent *event){
}

void mouseMoveEvent(QMouseEvent *event){
}

void mouseReleaseEvent(QMouseEvent *event){
}

void wheelEvent(QWheelEvent *event){
}

void keyPressEvent(QKeyEvent *event){
}

void keyRepeatEvent(QKeyEvent *event){
}

void keyReleaseEvent(QKeyEvent *event){
}
