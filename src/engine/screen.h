#ifndef SCREEN_H
#define SCREEN_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>



class Graphics;
class Application;

class Screen{
public:
    Screen(Application* application);
    ~Screen();

public:
    virtual void onSwitch();

    virtual void tick(float seconds) = 0;
    virtual void draw(Graphics *g) = 0;

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
    virtual void wheelEvent(QWheelEvent *event) = 0;
    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyRepeatEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *event) = 0;

    virtual void resize(int w, int h) = 0;

    void setParentApplication(Application* app);

protected:
    Application* application;
};

#endif // SCREEN_H
