#ifndef NAVMESH_H
#define NAVMESH_H

#include "engine/util/CommonIncludes.h"
#include <vector>
#include <QGLWidget>

class NavRegion{
public:
    NavRegion(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    bool isAdjacent(std::shared_ptr<NavRegion> other);
    float distanceToPoint(glm::vec3 p);
    glm::vec3 getCenter();

//    bool operator==(const NavRegion &other) const{
//        int shared = 0;
//        for(glm::vec3 a : this->points){
//            for(glm::vec3 b : other.points){
//                if(a == b) shared++;
//                if(shared >= 3) return true;
//            }
//        }
//        return false;
//    }

    QList<glm::vec3> points;
    std::shared_ptr<QList<std::shared_ptr<NavRegion>>> adjacent;
};

//bool operator==(const NavRegion& A, const NavRegion& B){
//    int shared = 0;
//    for(glm::vec3 a : A.points){
//        for(glm::vec3 b : B.points){
//            if(a == b) shared++;
//            if(shared >= 3) return true;
//        }
//    }
//    return false;
//}

class NavMesh{
public:
    NavMesh(const std::vector<float> &m_positions);

    void findPath(glm::vec3 start, glm::vec3 end, std::shared_ptr<QList<std::shared_ptr<NavRegion>>> path);

private:
    std::shared_ptr<NavRegion> nearestNavRegion(glm::vec3 p);

public:

    std::shared_ptr<QList<std::shared_ptr<NavRegion>>> regions;
};

#endif // NAVMESH_H
