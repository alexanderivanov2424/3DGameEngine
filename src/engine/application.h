#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

class Graphics;
class Camera;
class Screen;

class Application
{
public:
    Application();
    ~Application();

public:
    void tick(float seconds);
    void draw(Graphics *g);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void setCurrentScreen(std::string screenTag);
    Screen* getCurrentScreen();

public:
    std::shared_ptr<Camera> m_camera;

private:
    std::map<std::string, *Screen> screens;
    std::string currentScreen;

};

#endif // APPLICATION_H
