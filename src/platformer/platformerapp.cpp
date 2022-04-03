#include "platformerapp.h"

#include<QDebug>

#include "platformer/platformerscreen.h"
#include "view.h"

#include "OBJLoader.h"
#include "engine/graphics/Shape.h"

#include "engine/shapes/mesh.h"

PlatformerApp::PlatformerApp(View* view, int w, int h) : Application(view, w, h){

}

PlatformerApp::~PlatformerApp(){

}

void PlatformerApp::onStartup(Graphics *g){
    Material playerMaterial;
    playerMaterial.color = glm::vec3(0, 0, 1);
    g->addMaterial("player", playerMaterial);

    Material red;
    red.color = glm::vec3(1, 0, 0);
    g->addMaterial("red", red);

    Material blue;
    blue.color = glm::vec3(0, 1, 0);
    g->addMaterial("blue", blue);

    Material green;
    green.color = glm::vec3(0, 0, 1);
    g->addMaterial("green", green);

    Material mySecondMaterial;
    mySecondMaterial.textureName = "grass";
    g->addMaterial("grass", mySecondMaterial);

    OBJData obj = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//level_easy.obj");
    const std::shared_ptr<Shape> &mesh_shape = std::make_shared<Shape>(
                (const std::vector<float>) obj.positions,
                (const std::vector<float>) obj.normals,
                (const std::vector<float>) obj.uvs);
    g->addShape("mesh", mesh_shape);



    gameScreen = std::make_shared<PlatformerScreen>((std::shared_ptr<Application>)this);

    Application::addScreen("gameScreen", gameScreen);



}

