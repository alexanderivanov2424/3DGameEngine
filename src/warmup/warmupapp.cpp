#include "warmupapp.h"
#include <iostream>

#include "warmup/titlescreen.h"
#include "warmup/gamescreen.h"
#include "view.h"

WarmupApp::WarmupApp(View* view, int w, int h) : Application(view, w, h){

}

WarmupApp::~WarmupApp(){

}

void WarmupApp::onStartup(Graphics *g){

    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0, 1, 0);
    g->addMaterial("boringGreen", myFirstMaterial);

    Material mySecondMaterial;
    myFirstMaterial.textureName = "grass";
    g->addMaterial("grass", myFirstMaterial);


    titleScreen = std::make_shared<TitleScreen>(this);
    gameScreen = std::make_shared<GameScreen>(this);

    Application::addScreen("titleScreen", titleScreen);
    Application::addScreen("gameScreen", gameScreen);
}
