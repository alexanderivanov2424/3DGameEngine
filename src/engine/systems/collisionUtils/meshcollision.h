#ifndef MESHCOLLISION_H
#define MESHCOLLISION_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

class Mesh;
class Triangle;
class Ellipsoid;


struct Collision{
    bool isCollision;
    float t;
    glm::vec3 contact;
    glm::vec3 normal;
    Collision() : isCollision(false), t(0),  contact(glm::vec3(0,0,0)), normal(glm::vec3(0,0,0)){}
    Collision(float t, glm::vec3 contact, glm::vec3 normal) : isCollision(true), t(t), contact(contact), normal(normal){}
};

struct InvalidCollision : public std::exception{
    const char * what () const throw (){
        return "Invalid Collision";
    }
};

class MeshCollision
{
public:
    static Collision collide(std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos);
    static Collision slide(std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos);

private:
    static Collision SphereTriangleCollision(glm::vec3 A, glm::vec3 B, Triangle triangle);
    static Collision SphereEdgeCollision(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D);
    static Collision SpherePointCollision(glm::vec3 A, glm::vec3 B, glm::vec3 C);
    static float RayTriangleCollision(glm::vec3 p, glm::vec3 d, Triangle triangle);
    static float RaySphereCollision(glm::vec3 p, glm::vec3 d, glm::vec3 x);
};

#endif // MESHCOLLISION_H
