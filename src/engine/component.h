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

    virtual void tick(float seconds){};
    virtual void draw(Graphics *g){};

    virtual void mousePressEvent(QMouseEvent *event){};
    virtual void mouseMoveEvent(QMouseEvent *event){};
    virtual void mouseReleaseEvent(QMouseEvent *event){};
    virtual void wheelEvent(QWheelEvent *event){};
    virtual void keyPressEvent(QKeyEvent *event){};
    virtual void keyRepeatEvent(QKeyEvent *event){};
    virtual void keyReleaseEvent(QKeyEvent *event){};

public:
    std::shared_ptr<GameObject> gameObject;
};

#endif // COMPONENT_H
