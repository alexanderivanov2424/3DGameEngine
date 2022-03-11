#ifndef SYSTEM_H
#define SYSTEM_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

class Component;
class Graphics;

enum SystemFlag {
    NO_SYSTEM = 0,
    TICK_SYSTEM = 1,
    DRAW_SYSTEM = 2,
    COLLISION_SYSTEM = 4,
    INPUT_SYSTEM = 8
};

inline SystemFlag operator|(SystemFlag a, SystemFlag b){
    return static_cast<SystemFlag>(static_cast<int>(a) | static_cast<int>(b));
}


class System {
public:
    System();

    virtual SystemFlag systemFlag(){return NO_SYSTEM;};

    void addComponent(std::shared_ptr<Component> c);
    bool removeComponent(std::shared_ptr<Component> c);

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    QList<std::shared_ptr<Component>> components;
};

#endif // SYSTEM_H
