#include "warmupapp.h"

#include <QDebug>

#include "warmup/menuscreen.h"
#include "warmup/gamescreen.h"
#include "view.h"



WarmupApp::WarmupApp(View* view, int w, int h) : Application(view, w, h){

}

WarmupApp::~WarmupApp(){

}

void WarmupApp::onStartup(Graphics *g){
    qCritical() << "startup";

    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0, 1, 0);
    g->addMaterial("boringGreen", myFirstMaterial);

    Material mySecondMaterial;
    myFirstMaterial.textureName = "grass";
    g->addMaterial("grass", myFirstMaterial);

    qCritical() << "make screen";
    menuScreen = std::make_shared<MenuScreen>((std::shared_ptr<Application>)this);
//    gameScreen = std::make_shared<GameScreen>((std::shared_ptr<Application>)this);

    qCritical() << "add screen";
    Application::addScreen("menuScreen", menuScreen);
//    Application::addScreen("gameScreen", gameScreen);

    qCritical() << "done";
}
