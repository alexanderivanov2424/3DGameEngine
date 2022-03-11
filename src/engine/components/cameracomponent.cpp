#include "cameracomponent.h"

#include <QApplication>
#include <QWindow>
#include <QKeyEvent>
#include <QDebug>

#include "view.h"
#include "engine/application.h"
#include "engine/screen.h"

#include "engine/gameobject.h"
#include "engine/gameworld.h"
#include "engine/graphics/Camera.h"

#include "engine/components/transformcomponent.h"

CameraComponent::CameraComponent(std::shared_ptr<GameObject> g) : Component(g){

}


void CameraComponent::tick(float seconds){
    std::shared_ptr<TransformComponent> transform = this->gameObject->getComponent<TransformComponent>();
    std::shared_ptr<Camera> camera = this->gameObject->gameWorld->getCamera();

    glm::vec3 look = camera->getLook();
    camera->setEye(transform->transform - zoom * look + glm::vec3(0,1,0));
}


void CameraComponent::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0){
        zoom -= 1;
        if(zoom < 0) zoom = 0;
    } else if(event->angleDelta().y() < 0){
        zoom += 1;
    }
}

void CameraComponent::mouseMoveEvent(QMouseEvent *event){
    std::shared_ptr<Camera> camera = this->gameObject->gameWorld->getCamera();
    std::shared_ptr<Application> application = this->gameObject->gameWorld->screen->application;

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
