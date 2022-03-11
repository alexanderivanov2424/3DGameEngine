#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/util/CommonIncludes.h"

#include <QGLWidget>

class Screen;

class Graphics;
class GameObject;
class Camera;

class System;

class GameWorld{
public:
    GameWorld(std::shared_ptr<Screen> screen);

    void addGameObject(std::shared_ptr<GameObject> g);
    bool removeGameObject(std::shared_ptr<GameObject> g);

    void addSystem(std::shared_ptr<System> sys);
    bool removeSystem(std::shared_ptr<System> sys);

    std::shared_ptr<QMap<int, bool>> getKeyMap();
    std::shared_ptr<Camera> getCamera();

    virtual void tick(float seconds);
    virtual void draw(Graphics *g);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);


public:
    std::shared_ptr<Screen> screen;
    QList<std::shared_ptr<GameObject>> gameObjects;

    QList<std::shared_ptr<System>> systems;
};

#endif // GAMEWORLD_H
