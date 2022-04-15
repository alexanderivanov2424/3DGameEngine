#include "meshcollision.h"

#include <math.h>
#include <algorithm>

#include <QDebug>

#include "engine/component.h"
#include "engine/components/cylindercollisioncomponent.h"

#include "engine/shapes/mesh.h"
#include "engine/shapes/ellipsoid.h"


float smallestPositiveRoot(float a, float b, float c){
    float t;

    if(a == 0){
        t = -1 * c / b;
        if(t > 0) return t;

        throw InvalidCollision();
    }

    float d = b*b - 4 * a * c;
    if(d < 0) throw InvalidCollision();
    d = sqrt(d);
    float t1 = (-b + d)/(2 * a);
    float t2 = (-b - d)/(2 * a);
    if(t1 < 0 && t2 < 0) throw InvalidCollision();

    if(t1 < 0){
        t = t2;
    } else if (t2 < 0){
        t = t1;
    } else {
        t = std::min(t1,t2);
    }
    return t;
}

Collision MeshCollision::slide(std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos){
    glm::vec3 A = ellipse->m_pos;
    glm::vec3 B = nextPos;
    glm::vec3 direction = B-A;

    float totalDistance = glm::length(B-A);
    float timeLeft = 1;
    bool wasCollision = false;
    glm::vec3 lastNormal = glm::vec3(0,0,0);

    for(int itter = 0; itter < 5; itter++){
        ellipse->m_pos = A;
        Collision c = collide(mesh, ellipse, A + direction);

//        qCritical() << A[0] << " " << A[1] << " " << A[2] << " " << "START" << " ";
//        qCritical() << (A + direction)[0] << " " << (A + direction)[1] << " " << (A + direction)[2] << " ";


        A = c.isCollision ? c.contact : A + direction; //imediately set A to be final point of previous slide
        timeLeft -= c.t * (1 - timeLeft);
        if(timeLeft <= 0) break;
        if(glm::length2(c.normal) == 0) break;
        wasCollision = wasCollision || c.isCollision;
        lastNormal = c.normal;

        direction = direction - glm::dot(direction, c.normal) * c.normal;

        if(glm::length2(direction) == 0) break; //no direction to slide;

        direction = glm::normalize(direction) * timeLeft * totalDistance; // travel what is left
        A += .001f * c.normal;
    }
    if(wasCollision){
        return Collision(1 - timeLeft, A, lastNormal);
    }
    return Collision();

}

Collision MeshCollision::collide(std::shared_ptr<Mesh> mesh, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos){
    glm::vec3 scale = ellipse->m_radii;

    glm::vec3 A = ellipse->m_pos / scale;
    glm::vec3 B = nextPos / scale;

    Collision nearestCollision;
    for(std::shared_ptr<Triangle> t_ptr : mesh->m_triangles){
        Triangle t = *t_ptr;

        Triangle t_scaled = (t) / scale;

        Collision c;

        c = SphereTriangleCollision(A, B, t_scaled);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v1, t_scaled.v2);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v2, t_scaled.v3);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v3, t_scaled.v1);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v1);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v2);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v3);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }
    }

    nearestCollision.contact = nearestCollision.contact * scale;
    if(glm::length2(nearestCollision.normal) != 0){
        nearestCollision.normal = glm::normalize(nearestCollision.normal * scale);
    }

    return nearestCollision;
}

Collision MeshCollision::slide(std::shared_ptr<KDTreeCollision<Triangle>> kDTree, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos){
    glm::vec3 A = ellipse->m_pos;
    glm::vec3 B = nextPos;
    glm::vec3 direction = B-A;

    float totalDistance = glm::length(B-A);
    float timeLeft = 1;
    bool wasCollision = false;
    glm::vec3 lastNormal = glm::vec3(0,0,0);

    for(int itter = 0; itter < 5; itter++){
        ellipse->m_pos = A;
        Collision c = collide(kDTree, ellipse, A + direction);

//        qCritical() << A[0] << " " << A[1] << " " << A[2] << " " << "START" << " ";
//        qCritical() << (A + direction)[0] << " " << (A + direction)[1] << " " << (A + direction)[2] << " ";


        A = c.isCollision ? c.contact : A + direction; //imediately set A to be final point of previous slide
        timeLeft -= c.t * (1 - timeLeft);
        if(timeLeft <= 0) break;
        if(glm::length2(c.normal) == 0) break;
        wasCollision = wasCollision || c.isCollision;
        lastNormal = c.normal;

        direction = direction - glm::dot(direction, c.normal) * c.normal;

        if(glm::length2(direction) == 0) break; //no direction to slide;

        direction = glm::normalize(direction) * timeLeft * totalDistance; // travel what is left
        A += .001f * c.normal;
    }
    if(wasCollision){
        return Collision(1 - timeLeft, A, lastNormal);
    }
    return Collision();

}

Collision MeshCollision::collide(std::shared_ptr<KDTreeCollision<Triangle>> kDTree, std::shared_ptr<Ellipsoid> ellipse, glm::vec3 nextPos){
    glm::vec3 scale = ellipse->m_radii;

    glm::vec3 A = ellipse->m_pos / scale;
    glm::vec3 B = nextPos / scale;


    //std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> nearest = kDTree->collideBox(ellipse->m_pos - scale, 2.0f * scale);
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<Triangle>>>> nearest = kDTree->nearestK(ellipse->m_pos, 20);
    //nearest->append(*(kDTree->nearestK(nextPos, 20)));

    //qCritical() << nearest->length();

    Collision nearestCollision;
    for(int i = 0; i < nearest->length(); i++){
        Triangle t = *(nearest->at(i)->obj);

        Triangle t_scaled = (t) / scale;

        Collision c;

        c = SphereTriangleCollision(A, B, t_scaled);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v1, t_scaled.v2);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v2, t_scaled.v3);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SphereEdgeCollision(A, B, t_scaled.v3, t_scaled.v1);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v1);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v2);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }

        c = SpherePointCollision(A, B, t_scaled.v3);
        if(c.isCollision){
            if(!nearestCollision.isCollision || c.t < nearestCollision.t){
                nearestCollision = c;
            }
            continue;
        }
    }

    nearestCollision.contact = nearestCollision.contact * scale;
    if(glm::length2(nearestCollision.normal) != 0){
        nearestCollision.normal = glm::normalize(nearestCollision.normal * scale);
    }

    return nearestCollision;
}


/*
 * Checks if sphere with radius 1 collides with point C when moving from A to B
 * A - sphere initial position
 * B - sphere end position
 * C - point
 *
 * return Collision struct with collision time, point, and normal or
 *      throws InvalidCollision exception if no collision
 */
Collision MeshCollision::SpherePointCollision(glm::vec3 A, glm::vec3 B, glm::vec3 C){
//    if(glm::length2(B-C) > glm::length2(A-C)){ //moving away from point
//        return Collision();
//    }

    float a = glm::dot(B-A, B-A);
    float b = 2*glm::dot(A-C, B-A);
    float c = glm::dot(A-C, A-C) - 1;

    float t;
    try{
        t = smallestPositiveRoot(a,b,c);
    } catch(InvalidCollision& e){
        return Collision();
    }
    if(t > 1) return Collision();
    return Collision(t, A + t * (B-A), glm::normalize(A + t * (B-A) - C));
}

/*
 * Checks if sphere with radius 1 collides with edge CD when moving from A to B
 * A - sphere initial position
 * B - sphere end position
 * C - first edge endpoint
 * D - second edge endpoint
 *
 * return Collision struct with collision time, point, and normal or
 *      throws InvalidCollision exception if no collision
 */
Collision MeshCollision::SphereEdgeCollision(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D){
//    float d1 = glm::length2(glm::cross(D-C, C-A))/glm::length2(D-C);
//    float d2 = glm::length2(glm::cross(D-C, C-B))/glm::length2(D-C);
//    if(d2 >= d1){ //moving away from edge
//        return Collision();
//    }

    float a = glm::length2(glm::cross(B-A, D-C));
    float b = glm::dot( 2.0f * glm::cross(B-A, D-C), glm::cross(A-C, D-C));
    float c = glm::length2(glm::cross(A-C, D-C)) - glm::length2(D-C);

    float t;
    try{
        t = smallestPositiveRoot(a,b,c);
    } catch(InvalidCollision& e){
        return Collision();
    }
    if(t > 1) return Collision();

    glm::vec3 p = A + (B-A)*t;
    float edgeProj = glm::dot(p-C, D-C);
    if(edgeProj < 0 || edgeProj > glm::length2(D-C)){
        return Collision();
    }
    return Collision(t, p, glm::normalize(p - (C + (edgeProj / glm::length2(D-C)) * (D-C))));
}

/*
 * Checks if sphere with radius 1 collides with triangle when moving from A to B
 * A - sphere initial position
 * B - sphere end position
 * triangle - triangle to check collision with.
 *
 * return Collision struct with collision time, point, and normal or
 *      throws InvalidCollision exception if no collision
 *
 */
Collision MeshCollision::SphereTriangleCollision(glm::vec3 A, glm::vec3 B, Triangle triangle){
//    float d1 = glm::length2(glm::dot(triangle.normal, A - triangle.v1));
//    float d2 = glm::length2(glm::dot(triangle.normal, B - triangle.v1));
//    // and glm::dot(triangle.normal, A-triangle.v1) * glm::dot(triangle.normal, B-triangle.v1) > 0
//    if(d2 >= d1){ //moving away from triangle
//        return Collision();
//    }

    if(glm::dot(triangle.normal, A-triangle.v1) < 0){
        triangle.normal = -triangle.normal;
    }

    float t;
    try{
        t = RayTriangleCollision(A - triangle.normal, B-A, triangle);
    } catch(InvalidCollision& e){
        return Collision();
    }
    if(t > 1) return Collision();


    return Collision(t, A + t*(B-A), triangle.normal);
}

/*
 * Finds the positive time t at which the ray from point p in direction d intersects  the interior of triangle
 * If no such t exists throws InvalidCollision exception
 */
float MeshCollision::RayTriangleCollision(glm::vec3 p, glm::vec3 d, Triangle triangle){
    float t = glm::dot(triangle.v1 - p, triangle.normal) / glm::dot(d, triangle.normal);
    if(t < 0 || t > 1) throw InvalidCollision();

    glm::vec3 x = p + t * d;

    float a = glm::dot(triangle.normal, glm::cross(triangle.v2-triangle.v1, x-triangle.v1));
    float b = glm::dot(triangle.normal, glm::cross(triangle.v3-triangle.v2, x-triangle.v2));
    float c = glm::dot(triangle.normal, glm::cross(triangle.v1-triangle.v3, x-triangle.v3));

    if((a > 0 && b > 0 && c > 0) || a < 0 && b < 0 && c < 0){
        return t;
    }
    throw InvalidCollision();
}

/*
 * Finds positive time t at which ray from point p in direction d intersects unit sphere at x
 *
 */
float MeshCollision::RaySphereCollision(glm::vec3 p, glm::vec3 d, glm::vec3 x){
    float a = glm::length2(d);
    float b = 2 * glm::dot(d, (x-p));
    float c = glm::length2(x-p) - 1;

    return smallestPositiveRoot(a,b,c);
}

