#ifndef SCREEN_H
#define SCREEN_H

#include "engine/util/CommonIncludes.h"
#include "engine/graphics/Camera.h"

#include <QGLWidget>


class Graphics;
class Application;
class GameWorld;

class Screen{
public:
    Screen(std::shared_ptr<Application> application);

public:
    virtual void onSwitch() = 0;

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void resize(int w, int h);

    void setParentApplication(std::shared_ptr<Application> app);

public:
    std::shared_ptr<Camera> camera;

protected:
    std::shared_ptr<Application> application;
    QMap<int, bool> keyMap;
    std::shared_ptr<GameWorld> gameWorld;

};

#endif // SCREEN_H
