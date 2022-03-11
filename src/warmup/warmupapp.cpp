#include "warmupapp.h"

#include <QDebug>

#include "warmup/menuscreen.h"
#include "warmup/gamescreen.h"
#include "warmup/endscreen.h"
#include "view.h"



WarmupApp::WarmupApp(View* view, int w, int h) : Application(view, w, h){

}

WarmupApp::~WarmupApp(){

}

void WarmupApp::onStartup(Graphics *g){
    Material playerMaterial;
    playerMaterial.color = glm::vec3(0, 0, 1);
    g->addMaterial("player", playerMaterial);

    Material tokenMaterial;
    tokenMaterial.color = glm::vec3(1, 0, 0);
    g->addMaterial("token", tokenMaterial);

    Material mySecondMaterial;
    mySecondMaterial.textureName = "grass";
    g->addMaterial("grass", mySecondMaterial);

    menuScreen = std::make_shared<MenuScreen>((std::shared_ptr<Application>)this);
    gameScreen = std::make_shared<GameScreen>((std::shared_ptr<Application>)this);
    endScreen = std::make_shared<EndScreen>((std::shared_ptr<Application>)this);

    Application::addScreen("menuScreen", menuScreen);
    Application::addScreen("gameScreen", gameScreen);
    Application::addScreen("endScreen", endScreen);

}
