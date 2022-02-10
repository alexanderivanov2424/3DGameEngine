#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#include "engine/graphics/GraphicsDebug.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

#include "engine/screen.h"


class GameScreen : public Screen{
public:
    GameScreen(Application* application);

public:
    void tick(float seconds) override;
    void draw(Graphics *g) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyRepeatEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void resize(int w, int h) override;

public:
    std::shared_ptr<Camera> camera;

private:
    QMap<int, bool> keyMap;
};

#endif // GAMESCREEN_H
