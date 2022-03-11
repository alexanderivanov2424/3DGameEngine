#include "application.h"

#include <QDebug>

#include "view.h"
#include "engine/screen.h"


Application::Application(View *view, int w, int h){
    this->view = view;

    width = w;
    height = h;
    origSize = glm::vec2(w,h);

    currentScreenTag = "";
    currentScreen = nullptr;
}

Application::~Application(){
    delete view;
}

void Application::addScreen(QString screenTag, std::shared_ptr<Screen> screen){
    screens[screenTag] = screen;
    if(currentScreen == nullptr){
        currentScreenTag = screenTag;
        currentScreen = screen;
    }
}

void Application::setCurrentScreen(QString screenTag){
    if(!screens.contains(screenTag)){
        qWarning() << "Screen '" << screenTag << "' Not in application";
        return;
    }
    currentScreenTag = screenTag;
    currentScreen = getCurrentScreen();
    currentScreen->onSwitch();
}

std::shared_ptr<Screen> Application::getCurrentScreen(){
    return screens[currentScreenTag];
}

void Application::onStartup(Graphics *g){

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
    width = w;
    height = h;
    currentScreen->resize(w, h);
}
