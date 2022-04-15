#include "enemyaicomponent.h"

#include <QDebug>

#include "engine/gameobject.h"
#include "engine/gameworld.h"

#include "engine/components/transformcomponent.h"
#include "engine/systems/collisionUtils/meshcollision.h"

#include "engine/shapes/mesh.h"
#include "engine/shapes/ellipsoid.h"

#include "engine/graphics/Graphics.h"

#include "engine/AILib/navmesh.h"

WalkTowardsPlayer::WalkTowardsPlayer(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> enemy) : BTActionNode(){
    this->player = player;
    this->enemy = enemy;
}

void print(glm::vec3 v){
    qCritical() << v[0] << " " << v[1] << " " << v[2];
}

Status WalkTowardsPlayer::tick(float seconds){
    std::shared_ptr<TransformComponent> playerTransform = this->player->getComponent<TransformComponent>();
    std::shared_ptr<TransformComponent> enemyTransform = this->enemy->getComponent<TransformComponent>();

    std::shared_ptr<EnemyAIComponent> enemyAI = this->enemy->getComponent<EnemyAIComponent>();

    if(path == nullptr || path->length() == 0){
        path = std::make_shared<QList<std::shared_ptr<NavRegion>>>();
        enemyAI->navMesh->findPath(enemyTransform->transform, playerTransform->transform, path);
    }

    float d = 2 * seconds;
    std::shared_ptr<NavRegion> current;
    while(d > 0 && path->length() > 0){
        current = path->at(0);


        glm::vec2 goal = glm::vec2(current->getCenter()[0], current->getCenter()[2]);
        glm::vec2 enemyPos = glm::vec2(enemyTransform->transform[0], enemyTransform->transform[2]);

        enemyAI->ellipsoid->m_pos = enemyTransform->transform;


        float distanceToNext = glm::length(goal - enemyPos);

        if(distanceToNext < d){
            glm::vec3 next_pos = current->getCenter();
            next_pos[1] += enemyAI->ellipsoid->m_radii[1] * 2;
            enemyTransform->transform = next_pos;
            d -= distanceToNext;
            path->removeOne(current);
            continue;
        }

        glm::vec2 movement2D = (goal - enemyPos);
        glm::vec3 movement = d * glm::normalize(glm::vec3(movement2D[0], 0, movement2D[1]));
        glm::vec3 next_pos = enemyTransform->transform + movement;


//        qCritical() << "test";
//        print(current->getCenter());
//        print(playerTransform->transform);
//        print(enemyTransform->transform);

//        print(movement);
//        print(next_pos);



        Collision c;
        if(enemyAI->mesh){
            c = MeshCollision::slide(enemyAI->mesh, enemyAI->ellipsoid, next_pos);
        } else if(enemyAI->kDTree){
            c = MeshCollision::slide(enemyAI->kDTree, enemyAI->ellipsoid, next_pos);
        }

        if(c.isCollision){
            enemyTransform->transform = c.contact;
        } else {
            enemyTransform->transform = next_pos;
        }
        d = 0;

    }

    enemyAI->ellipsoid->m_pos = enemyTransform->transform + glm::vec3(0,1,0);
    glm::vec3 next_pos = enemyTransform->transform + glm::vec3(0,-1,0);

    Collision c;
    if(enemyAI->mesh){
        c = MeshCollision::collide(enemyAI->mesh, enemyAI->ellipsoid, next_pos);
    } else if(enemyAI->kDTree){
        c = MeshCollision::collide(enemyAI->kDTree, enemyAI->ellipsoid, next_pos);
    }
    if(c.isCollision){
        enemyTransform->transform = c.contact;
    }

    return SUCCESS;
}

void WalkTowardsPlayer::reset(){

}


IsPlayerFar::IsPlayerFar(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> enemy) : BTConditionNode(){
    this->player = player;
    this->enemy = enemy;
}

void IsPlayerFar::reset(){

}

bool IsPlayerFar::checkCondition(float seconds){
    std::shared_ptr<TransformComponent> playerTransform = this->player->getComponent<TransformComponent>();
    std::shared_ptr<TransformComponent> enemyTransform = this->enemy->getComponent<TransformComponent>();

    if(glm::length(playerTransform->transform - enemyTransform->transform) > 5){
        return true;
    }
    return false;
}

EnemyAIComponent::EnemyAIComponent(std::shared_ptr<GameObject> g, std::shared_ptr<GameObject> player, std::shared_ptr<Ellipsoid> ellipsoid, std::shared_ptr<NavMesh> navMesh, std::shared_ptr<Mesh> mesh)  : AIComponent(g){
    this->player = player;
    this->mesh = mesh;
    this->navMesh = navMesh;
    this->ellipsoid = ellipsoid;


    IsPlayerFar a = IsPlayerFar(player, g);
    std::shared_ptr<BTSequenceNode> ai = std::make_shared<BTSequenceNode>();
    ai->linkChild(std::make_shared<IsPlayerFar>(player, g));
    ai->linkChild(std::make_shared<WalkTowardsPlayer>(player, g));

    this->setBTNode(ai);
}

EnemyAIComponent::EnemyAIComponent(std::shared_ptr<GameObject> g, std::shared_ptr<GameObject> player, std::shared_ptr<Ellipsoid> ellipsoid, std::shared_ptr<NavMesh> navMesh, std::shared_ptr<KDTreeCollision<Triangle>> kDTree)  : AIComponent(g){
    this->player = player;
    this->kDTree = kDTree;
    this->navMesh = navMesh;
    this->ellipsoid = ellipsoid;

    std::shared_ptr<BTSequenceNode> ai = std::make_shared<BTSequenceNode>();
    ai->linkChild(std::make_shared<IsPlayerFar>(player, g));
    ai->linkChild(std::make_shared<WalkTowardsPlayer>(player, g));

    this->setBTNode(ai);
}


