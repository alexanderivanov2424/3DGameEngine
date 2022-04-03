#include "platformerscreen.h"

#include <QApplication>
#include <QWindow>
#include <QKeyEvent>
#include <QDebug>

#include "view.h"
#include "engine/application.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"
#include "engine/systems/inputsystem.h"

#include "engine/gameworld.h"
#include "engine/gameobject.h"
#include "engine/component.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/meshslidecomponent.h"
#include "engine/components/cameracomponent.h"
#include "engine/components/ellipsoidcomponent.h"

#include "OBJLoader.h"
#include "engine/shapes/mesh.h"

PlatformerScreen::PlatformerScreen(std::shared_ptr<Application> application) : Screen(application){
    OBJData obj = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//level_easy.obj");
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(obj.positions, obj.normals);


    player = std::make_shared<GameObject>(gameWorld);
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player, glm::vec3(1,6,1)));
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(player));

    std::shared_ptr<Ellipsoid> ellipsoid = std::make_shared<Ellipsoid>(glm::vec3(.25,.25,.25));

    player->addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(player, ellipsoid, "player"));
    player->addComponent<MeshSlideComponent>(std::make_shared<MeshSlideComponent>(player, mesh, ellipsoid));
    gameWorld->addGameObject(player);
}


void PlatformerScreen::onSwitch(){
    QApplication::setOverrideCursor(Qt::BlankCursor);
    player->getComponent<TransformComponent>()->transform = glm::vec3(0,0,0);
}


void PlatformerScreen::draw(Graphics *g){
    Screen::draw(g);
    int w = application->width;
    int h = application->height;
    camera->setScreenSize(glm::vec2(w, h));
    g->setCamera(camera);

//    for(int i = 0; i<10; i++){
//        for(int j = 0; j<10; j++){
//            g->clearTransform();
//            g->scale(20);
//            g->translate(glm::vec3(i,0,j));
//            g->setMaterial("grass");
//            g->drawShape("quad");
//        }
//    }

    g->clearTransform();
    g->translate(glm::vec3(0,0,0));
    g->setMaterial("grass");
    g->drawShape("mesh");

}

void PlatformerScreen::keyPressEvent(QKeyEvent *event){
    Screen::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape) QApplication::quit();
}

