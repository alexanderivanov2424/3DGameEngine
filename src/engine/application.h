#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>


class Graphics;
class Screen;
class View;

class Application{
public:
    Application(View *view, int w, int h);
    ~Application();

public:
    virtual void onStartup(Graphics *g);

    void tick(float seconds);
    void draw(Graphics *g);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void resize(int w, int h);

    void addScreen(QString screenTag, std::shared_ptr<Screen> screen);
    void setCurrentScreen(QString screenTag);
    std::shared_ptr<Screen> getCurrentScreen();

public:

    View *view;
    int width = 0;
    int height = 0;

private:
    QMap<QString, std::shared_ptr<Screen>> screens;
    QString currentScreenTag;
    std::shared_ptr<Screen> currentScreen;

};

#endif // APPLICATION_H
