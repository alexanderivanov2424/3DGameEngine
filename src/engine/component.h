#ifndef COMPONENT_H
#define COMPONENT_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

#include "engine/systems/system.h"

class Graphics;
class GameObject;

class Component{
public:
    Component(std::shared_ptr<GameObject> gameObject);

    virtual SystemFlag requiresSystems() = 0;

    virtual void tick(float seconds) = 0;
    virtual void draw(Graphics *g) = 0;

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
    virtual void wheelEvent(QWheelEvent *event) = 0;
    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyRepeatEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *event) = 0;

private:
    std::shared_ptr<GameObject> gameObject;
};

#endif // COMPONENT_H
