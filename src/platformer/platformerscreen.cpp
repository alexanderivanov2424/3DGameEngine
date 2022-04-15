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

#include "engine/graphics/Shape.h"

#include "engine/AILib/navmesh.h"

#include "platformer/enemyaicomponent.h"

PlatformerScreen::PlatformerScreen(std::shared_ptr<Application> application) : Screen(application){
//    OBJData objSmall = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//level_easy.obj");
//    meshSmall = std::make_shared<Mesh>(objSmall.positions, objSmall.normals);

//    pointsSmall = std::make_shared<QList<std::shared_ptr<KDTreePoint<Triangle>>>>();
//    for(std::shared_ptr<Triangle> t : meshSmall->m_triangles){
//        pointsSmall->append(std::make_shared<KDTreePoint<Triangle>>((t->v1 + t->v2 + t->v3)/3.0f, t));
//    }

//    OBJData obj = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//large_environment.obj");
//    mesh = std::make_shared<Mesh>(obj.positions, obj.normals);


//    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> points =
//            std::make_shared<QList<std::shared_ptr<KDTreePoint<Triangle>>>>();
//    for(std::shared_ptr<Triangle> t : mesh->m_triangles){
//        points->append(std::make_shared<KDTreePoint<Triangle>>((t->v1 + t->v2 + t->v3)/3.0f, t));
//    }


    OBJData obj = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//level_easy.obj");
    mesh = std::make_shared<Mesh>(obj.positions, obj.normals);

    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> points =
                std::make_shared<QList<std::shared_ptr<KDTreePoint<Triangle>>>>();
    for(std::shared_ptr<Triangle> t : mesh->m_triangles){
        points->append(std::make_shared<KDTreePoint<Triangle>>((t->v1 + t->v2 + t->v3)/3.0f, t));
    }

    kDTree = std::make_shared<KDTreeCollision<Triangle>>(points);

    player = std::make_shared<GameObject>(gameWorld);
    player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player, glm::vec3(1,6,1)));
    //player->addComponent<TransformComponent>(std::make_shared<TransformComponent>(player, glm::vec3(-50,100,-50)));
    player->addComponent<CameraComponent>(std::make_shared<CameraComponent>(player));

    std::shared_ptr<Ellipsoid> ellipsoid = std::make_shared<Ellipsoid>(glm::vec3(.25,.25,.25));

    player->addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(player, ellipsoid, "player"));
    player->addComponent<MeshSlideComponent>(std::make_shared<MeshSlideComponent>(player, kDTree, ellipsoid));
    gameWorld->addGameObject(player);


    OBJData navMeshSmall = OBJLoader::loadOBJ("C://Users//Alexander\ Ivanov//Desktop//3D\ Game\ Engines//engine//engine//res//obj//level_easy_navmesh.obj");
    navMesh = std::make_shared<NavMesh>(navMeshSmall.positions);


    std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>(gameWorld);
    enemy->addComponent<TransformComponent>(std::make_shared<TransformComponent>(enemy, glm::vec3(4,3,4)));
    std::shared_ptr<Ellipsoid> enemyEllipsoid = std::make_shared<Ellipsoid>(glm::vec3(.25,.25,.25));
    enemy->addComponent<EllipsoidComponent>(std::make_shared<EllipsoidComponent>(enemy, enemyEllipsoid, "blue"));


    enemy->addComponent<EnemyAIComponent>(std::make_shared<EnemyAIComponent>(enemy, player, enemyEllipsoid, navMesh, mesh));
    std::shared_ptr<EnemyAIComponent> enemyAI = enemy->getComponent<EnemyAIComponent>();
    gameWorld->addGameObject(enemy);
}


void PlatformerScreen::onSwitch(){
    QApplication::setOverrideCursor(Qt::BlankCursor);
    player->getComponent<TransformComponent>()->transform = glm::vec3(0,0,0);
}


void PlatformerScreen::tick(float seconds){
    Screen::tick(seconds);
}

void PlatformerScreen::draw(Graphics *g){
    Screen::draw(g);
    int w = application->width;
    int h = application->height;
    camera->setScreenSize(glm::vec2(w, h));
    g->setCamera(camera);

    g->clearTransform();
    g->translate(glm::vec3(0,0,0));
    g->setMaterial("grass");
    g->drawShape("mesh");

//    if(addedSmall){
//        g->clearTransform();
//        g->translate(glm::vec3(0,0,0));
//        g->setMaterial("grass");
//        g->drawShape("meshSmall");
//    }

    std::shared_ptr<TransformComponent> transform = player->getComponent<TransformComponent>();
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> nearest = kDTree->nearestK(transform->transform, 20);

    for(int i = 0; i < nearest->length(); i++){
        Triangle t = *(nearest->at(i)->obj);
        g->clearTransform();
        g->translate((t.v1 + t.v2 + t.v3) / 3.0f);
        g->scale(glm::vec3(.2,.2,.2));
        g->setMaterial("red");
        g->drawShape("sphere");
    }

}

void PlatformerScreen::keyPressEvent(QKeyEvent *event){
    Screen::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape) QApplication::quit();

//    if (event->key() == Qt::Key_U and !addedSmall){
//        for(int i = 0; i < pointsSmall->length(); i++){
//            kDTree->addPoint(pointsSmall->at(i));
//        }
//        addedSmall = true;
//    }
}

