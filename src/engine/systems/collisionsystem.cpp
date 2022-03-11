#include "collisionsystem.h"

#include <QDebug>

#include "engine/component.h"
#include "engine/components/cylindercollisioncomponent.h"

CollisionSystem::CollisionSystem() : System() {

}

SystemFlag CollisionSystem::systemFlag(){
    return COLLISION_SYSTEM;
}


void CollisionSystem::tick(float seconds){
    QList<std::shared_ptr<Component>>::iterator comp1;
    QList<std::shared_ptr<Component>>::iterator comp2;

    for(comp1 = components.begin(); comp1 != components.end() - 1; comp1++){
        if(dynamic_cast<CylinderCollisionComponent*>((*comp1).get()) == nullptr) continue;
        for(comp2 = comp1 + 1; comp2 != components.end(); comp2++){
            if(dynamic_cast<CylinderCollisionComponent*>((*comp2).get()) == nullptr) continue;

            CylinderCollisionComponent *c1 = dynamic_cast<CylinderCollisionComponent*>((*comp1).get());
            CylinderCollisionComponent *c2 = dynamic_cast<CylinderCollisionComponent*>((*comp2).get());

            if(c1->stationary && c2->stationary){
                continue;
            }

            glm::vec3 mtv = glm::vec3(0,0,0);

            glm::vec2 p1 = glm::vec2(c1->getAbsolutePosition()[0], c1->getAbsolutePosition()[2]);
            glm::vec2 p2 = glm::vec2(c2->getAbsolutePosition()[0], c2->getAbsolutePosition()[2]);


            float dist = glm::length(p1 - p2);
            glm::vec2 xzMtv = glm::vec2(0,0);
            if(dist < c1->radius + c2->radius){
                xzMtv = (p1 - p2) * (c1->radius + c2->radius - dist) / dist;
            } else {
                continue;
            }

            float yMtv = std::min(
                        (c1->getAbsolutePosition()[1] + c1->height) - c2->getAbsolutePosition()[1],
                        (c2->getAbsolutePosition()[1] + c2->height) - c1->getAbsolutePosition()[1]);

            if(yMtv < 0){
                continue;
            }

            if(c1->radius + c2->radius - dist < yMtv){
                mtv[0] = xzMtv[0];
                mtv[2] = xzMtv[1];
            } else {
                mtv[1] = yMtv;
            }

            if(c1->stationary){
                c2->applyMTV(mtv * (-1.0f));
            } else if (c2->stationary){
                c1->applyMTV(mtv);
            } else {
                c1->applyMTV(mtv * (0.5f));
                c2->applyMTV(mtv * (-0.5f));
            }

            if(c1->callback != nullptr) c1->callback(c1->gameObject);
            if(c2->callback != nullptr) c2->callback(c2->gameObject);

        }
    }
}
