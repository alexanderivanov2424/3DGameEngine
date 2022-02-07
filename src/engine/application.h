#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

#include "engine/screen.h"

class Graphics;
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

    void resize(int w, int h);

    void setCurrentScreen(QString screenTag);
    Screen* getCurrentScreen();

public:

private:
    QMap<QString, Screen*> screens;
    QString currentScreenTag;
    Screen* currentScreen;

};

#endif // APPLICATION_H
