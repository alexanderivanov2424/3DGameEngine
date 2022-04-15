#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include "engine/component.h"
#include "engine/components/aicomponent.h"

#include "engine/AILib/btnode.h"

#include "engine/shapes/ellipsoid.h"
#include "engine/systems/collisionUtils/kdtreecollision.h"
class Mesh;
class Triangle;
class NavMesh;
class NavRegion;


class EnemyAIComponent : public AIComponent{
public:
    EnemyAIComponent(std::shared_ptr<GameObject> g, std::shared_ptr<GameObject> player, std::shared_ptr<Ellipsoid> ellipsoid, std::shared_ptr<NavMesh> navMesh, std::shared_ptr<Mesh> mesh);

    EnemyAIComponent(std::shared_ptr<GameObject> g, std::shared_ptr<GameObject> player, std::shared_ptr<Ellipsoid> ellipsoid, std::shared_ptr<NavMesh> navMesh, std::shared_ptr<KDTreeCollision<Triangle>> kDTree);

    std::shared_ptr<GameObject> player;

    std::shared_ptr<Ellipsoid> ellipsoid;
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<KDTreeCollision<Triangle>> kDTree = nullptr;

    std::shared_ptr<NavMesh> navMesh;
};


class WalkTowardsPlayer : public BTActionNode{
public:
    WalkTowardsPlayer(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> enemy);

    Status tick(float seconds) override;
    void reset() override;

private:
    std::shared_ptr<QList<std::shared_ptr<NavRegion>>> path;

    std::shared_ptr<GameObject> player;
    std::shared_ptr<GameObject> enemy;
};


class IsPlayerFar : public BTConditionNode{
public:
    IsPlayerFar(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> enemy);
    bool checkCondition(float seconds) override;
    void reset() override;

private:
    std::shared_ptr<GameObject> player;
    std::shared_ptr<GameObject> enemy;
};


#endif // ENEMYAICOMPONENT_H
