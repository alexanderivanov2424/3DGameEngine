#ifndef PLATFORMERSCREEN_H
#define PLATFORMERSCREEN_H

#include "engine/util/CommonIncludes.h"
#include "engine/screen.h"

class Screen;
class Graphics;
class GameObject;

class System;
class TickSystem;
class DrawSystem;
class CollisionSystem;
class InputSystem;

class PlatformerScreen : public Screen {
public:
    PlatformerScreen(std::shared_ptr<Application> application);

    void onSwitch() override;

    void draw(Graphics *g) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    std::shared_ptr<GameObject> player;

    float playerY = 0, playerYVel = 0, playerX = 0;
};

#endif // PLATFORMERSCREEN_H
