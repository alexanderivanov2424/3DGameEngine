#include "collisionsystem.h"

#include <QDebug>

#include <math.h>
#include <algorithm>

#include "engine/component.h"
#include "engine/components/cylindercollisioncomponent.h"

#include "engine/shapes/mesh.h"
#include "engine/shapes/ellipsoid.h"


CollisionSystem::CollisionSystem() : System() {

}

SystemFlag CollisionSystem::systemFlag(){
    return COLLISION_SYSTEM;
}

void CollisionSystem::tick(float seconds){
    //TODO collision system has functions to compute collision but doesn't fully handle all collisions
}
