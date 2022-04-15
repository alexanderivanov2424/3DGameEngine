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


#include "engine/systems/collisionUtils/kdtreecollision.h"
class Mesh;
class Triangle;

class NavMesh;

class PlatformerScreen : public Screen {
public:
    PlatformerScreen(std::shared_ptr<Application> application);

    void onSwitch() override;

    void tick(float seconds) override;
    void draw(Graphics *g) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    std::shared_ptr<GameObject> player;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<KDTreeCollision<Triangle>> kDTree;

    bool addedSmall = false;
    std::shared_ptr<Mesh> meshSmall;
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> pointsSmall;

    std::shared_ptr<NavMesh> navMesh;

    float playerY = 0, playerYVel = 0, playerX = 0;
};

#endif // PLATFORMERSCREEN_H
