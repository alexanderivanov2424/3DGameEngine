#ifndef GAMESCREEN_H
#define GAMESCREEN_H

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

class GameScreen : public Screen {
public:
    GameScreen(std::shared_ptr<Application> application);

    void onSwitch() override;

    void draw(Graphics *g) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    std::shared_ptr<GameObject> player;

    std::shared_ptr<TickSystem> tickSystem;
    std::shared_ptr<DrawSystem> drawSystem;
    std::shared_ptr<CollisionSystem> collisionSystem;
    std::shared_ptr<InputSystem> inputSystem;

    float playerY = 0, playerYVel = 0, playerX = 0;
};

#endif // GAMESCREEN_H
