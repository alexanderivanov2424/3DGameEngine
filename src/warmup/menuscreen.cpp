#include "menuscreen.h"

#include <QApplication>
#include <QKeyEvent>
#include <QWindow>
#include <QDebug>

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

#include "engine/graphics/Font.h"

#include "engine/application.h"
#include "engine/systems/ticksystem.h"

#include "engine/gameworld.h"

MenuScreen::MenuScreen(std::shared_ptr<Application> application) : Screen(application){

}

void MenuScreen::onSwitch(){
    QApplication::restoreOverrideCursor();
}

void MenuScreen::draw(Graphics *g){
    g->setCamera(camera);

    int w = application->width;
    int h = application->height;

    camera->setUI(true);

    g->clearTransform();
    g->translate(glm::vec3(w/2 - 100,h/2 - 50,0));
    g->scale(glm::vec3(200,100,0));
    g->setColor(glm::vec3(0,0,255));
    g->drawShape("uiquad");

    g->clearTransform();
    FontMetrics fm = g->getFontMetrics("default", "start", 100.0f);
    g->translate(glm::vec3(w/2 - fm.width/2,h/2 - fm.ascent/2,0));
    g->setColor(glm::vec3(255,0,0));
    g->drawText("start", 100.0f);
}

void MenuScreen::mousePressEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    int w = application->width;
    int h = application->height;
    if(w/2 - 100 < mouseX && mouseX < w/2 + 100){
        if(h/2 - 50 < mouseY && mouseY < h/2 + 50){
            application->setCurrentScreen("gameScreen");
        }
    }
}

void MenuScreen::mouseMoveEvent(QMouseEvent *event){
    int deltaX = event->x() - application->width / 2;
    int deltaY = event->y() - application->height / 2;
    camera->rotate(-deltaX / 100.f, -deltaY / 100.f);
}




