#include "screen.h"
#include "engine/application.h"


Screen::Screen(Application* application){
    this->application = application;
}

Screen::~Screen(){
    delete application;
}

void Screen::setParentApplication(Application* app){
    application = app;
}

