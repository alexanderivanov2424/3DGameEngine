#ifndef MESHSLIDECOMPONENT_H
#define MESHSLIDECOMPONENT_H

#include "engine/component.h"

#include "engine/shapes/ellipsoid.h"

#include "engine/systems/collisionUtils/kdtreecollision.h"

class Mesh;
class Triangle;

class MeshSlideComponent : public Component{
public:
    MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<Mesh> mesh);
    MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipsoid);

    MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<KDTreeCollision<Triangle>> kDTree);
    MeshSlideComponent(std::shared_ptr<GameObject> g, std::shared_ptr<KDTreeCollision<Triangle>> kDTree, std::shared_ptr<Ellipsoid> ellipsoid);


    SystemFlag requiresSystems() override { return TICK_SYSTEM | DRAW_SYSTEM;}

    void tick(float seconds) override;

    void draw(Graphics *g) override;

private:
    float playerYVel = 0;
    bool onGround = false;

    bool DEBUG = false;

    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<KDTreeCollision<Triangle>> kDTree = nullptr;

    glm::vec3 root = glm::vec3(0,0,0);
    glm::vec3 bounce = glm::vec3(0,0,0);

    std::shared_ptr<Ellipsoid> ellipsoid;

};

#endif // MESHSLIDECOMPONENT_H
