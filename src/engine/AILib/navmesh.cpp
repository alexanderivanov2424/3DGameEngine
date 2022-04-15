#include "navmesh.h"
#include <QWindow>

#include <QDebug>

#include <cmath>

#include "engine/AILib/astar.h"

NavRegion::NavRegion(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3){
    points = QList<glm::vec3>();
    adjacent = std::make_shared<QList<std::shared_ptr<NavRegion>>>();

    points.append(v1);
    points.append(v2);
    points.append(v3);
}

bool NavRegion::isAdjacent(std::shared_ptr<NavRegion> other){
    int shared = 0;
    for(glm::vec3 a : this->points){
        for(glm::vec3 b : other->points){
            if(a == b) shared++;
            if(shared >= 2) return true;
        }
    }
    return false;
}

float NavRegion::distanceToPoint(glm::vec3 p){
    glm::vec3 v = p - points.at(0);
    glm::vec3 n = glm::cross(points.at(1) - points.at(0),points.at(2)-points.at(0));
    return std::abs(glm::dot(v,n));
}

glm::vec3 NavRegion::getCenter(){
    glm::vec3 avg = glm::vec3(0,0,0);
    for(glm::vec3 p : points){
        avg += p;
    }
    return avg / (float)(points.length());
}

NavMesh::NavMesh(const std::vector<float> &m_positions){
    regions = std::make_shared<QList<std::shared_ptr<NavRegion>>>();


    for(int i = 0; i < m_positions.size(); i+= 9){
        glm::vec3 v1 = glm::vec3(m_positions[i], m_positions[i+1], m_positions[i+2]);
        glm::vec3 v2 = glm::vec3(m_positions[i+3], m_positions[i+4], m_positions[i+5]);
        glm::vec3 v3 = glm::vec3(m_positions[i+6], m_positions[i+7], m_positions[i+8]);

        regions->append(std::make_shared<NavRegion>(v1,v2,v3));
    }


    for(int i = 0; i < regions->length() - 1; i++){
        for(int j = i + 1; j < regions->length(); j++){
            std::shared_ptr<NavRegion> a = regions->at(i);
            std::shared_ptr<NavRegion> b = regions->at(j);
            if(a->isAdjacent(b)){
                a->adjacent->append(b);
                b->adjacent->append(a);
            }
        }
    }
}

std::shared_ptr<NavRegion> NavMesh::nearestNavRegion(glm::vec3 p){
    std::shared_ptr<NavRegion> region = regions->at(0);
    float distance = glm::length2(region->getCenter() - p);//region->distanceToPoint(p);

    for(int i = 0; i < regions->length(); i++){
        std::shared_ptr<NavRegion> r = regions->at(i);
        float d = glm::length2(r->getCenter() - p);//r->distanceToPoint(p);
        if(d < distance){
            region = r;
            distance = d;
        }
    }
    return region;
}


auto getHeuristicFunction(glm::vec3 endPoint){
    return [endPoint](std::shared_ptr<NavRegion> region) -> float {
        return glm::length2(region->getCenter() - endPoint);
    };
}

float distanceFunction(std::shared_ptr<NavRegion> a, std::shared_ptr<NavRegion> b){
    return glm::length2(a->getCenter() - b->getCenter());
}

std::shared_ptr<QList<std::shared_ptr<NavRegion>>> adjacentFunction(std::shared_ptr<NavRegion> region){
    return region->adjacent;
}

void NavMesh::findPath(glm::vec3 start, glm::vec3 end, std::shared_ptr<QList<std::shared_ptr<NavRegion>>> regionPath){

    std::shared_ptr<NavRegion> startRegion = nearestNavRegion(start);
    std::shared_ptr<NavRegion> endRegion = nearestNavRegion(end);


    AStar<NavRegion> search = AStar<NavRegion>();
    search.findPath(regionPath, startRegion, endRegion, getHeuristicFunction(end), distanceFunction, adjacentFunction);
}
