#include "gamescreen.h"

#include <QApplication>
#include <QWindow>
#include <QKeyEvent>

#include "view.h"
#include "engine/application.h"
#include "engine/graphics/Graphics.h"

#include "engine/systems/system.h"
#include "engine/systems/ticksystem.h"
#include "engine/systems/drawsystem.h"
#include "engine/systems/collisionsystem.h"

#include "engine/gameworld.h"

GameScreen::GameScreen(std::shared_ptr<Application> application) : Screen(application){
    tickSystem = std::make_shared<TickSystem>();
    drawSystem = std::make_shared<DrawSystem>();
    collisionSystem = std::make_shared<CollisionSystem>();

    this->gameWorld->addSystem(tickSystem);
}

void GameScreen::onSwitch(){
    QApplication::setOverrideCursor(Qt::BlankCursor);
}

void GameScreen::tick(float seconds){
    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    dir *= .5f;
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);
    if(keyMap[Qt::Key_W]) camera->translate(dir);
    if(keyMap[Qt::Key_S]) camera->translate(-dir);
    if(keyMap[Qt::Key_A]) camera->translate(perp);
    if(keyMap[Qt::Key_D]) camera->translate(-perp);


    playerY += playerYVel * seconds;
    playerYVel += -20 * seconds;
    if(playerY <= 1){
        playerY = 1;
        playerYVel = 0;
    }
    if(keyMap[Qt::Key_Space] && playerY == 1){
        playerYVel = 10;
    }
    glm::vec3 camPos = camera->getEye();
    camera->setEye(glm::vec3(camPos.x, playerY, camPos.z));
}

void GameScreen::draw(Graphics *g){
    int w = application->width;
    int h = application->height;
    camera->setScreenSize(glm::vec2(w, h));
    g->setCamera(camera);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            g->clearTransform();
            g->scale(20);
            g->translate(glm::vec3(i,0,j));
            g->scale(19.0/20.0);
            g->setMaterial("grass");
            g->drawShape("quad");
        }
    }


    g->clearTransform();
    g->setDefaultMaterial();
    g->translate(glm::vec3(1.f, 1.f, 10.f));
    g->scale(5);
    g->drawShape("cylinder");
}

void GameScreen::mousePressEvent(QMouseEvent *event){}

void GameScreen::mouseMoveEvent(QMouseEvent *event){
    int w = application->width;
    int h = application->height;
    int deltaX = event->x() - w / 2;
    int deltaY = event->y() - h / 2;

    if (deltaX == 0 && deltaY == 0) {
        return;
    }

    QCursor::setPos(application->view->mapToGlobal(QPoint(w / 2, h / 2)));

    camera->rotate(-deltaX / 100.f, -deltaY / 100.f);
}

void GameScreen::mouseReleaseEvent(QMouseEvent *event){}

void GameScreen::wheelEvent(QWheelEvent *event){}

void GameScreen::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape) application->setCurrentScreen("titleScreen");
    keyMap[event->key()] = true;
}

void GameScreen::keyRepeatEvent(QKeyEvent *event){}

void GameScreen::keyReleaseEvent(QKeyEvent *event){
    Screen::keyReleaseEvent(event);
}
