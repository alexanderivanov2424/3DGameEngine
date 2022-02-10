#include "gamescreen.h"

#include <QApplication>
#include <QKeyEvent>
#include <QWindow>

#include<QDebug>

#include "view.h"
#include "engine/application.h"


GameScreen::GameScreen(Application* application) : Screen(application){
    camera = std::make_shared<Camera>();
    camera->setEye(glm::vec3(0, 1, 0));
}


void GameScreen::tick(float seconds){
    QApplication::setOverrideCursor(Qt::BlankCursor);

    glm::vec3 look = camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    dir *= .5;
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);
    if(keyMap[Qt::Key_W]) camera->translate(dir);
    if(keyMap[Qt::Key_S]) camera->translate(-dir);
    if(keyMap[Qt::Key_A]) camera->translate(perp);
    if(keyMap[Qt::Key_D]) camera->translate(-perp);
}

void GameScreen::draw(Graphics *g){
    g->setCamera(camera);

    g->clearTransform();
    g->scale(20);
    g->setMaterial("grass");
    g->drawShape("quad");

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
    keyMap[event->key()] = false;
}

void GameScreen::resize(int w, int h){
    camera->setScreenSize(glm::vec2(w, h));
}
