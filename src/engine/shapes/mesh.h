#ifndef MESH_H
#define MESH_H

#include "engine/util/CommonIncludes.h"
#include <vector>
#include <QGLWidget>

class Triangle{
public:
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normal){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->normal = glm::normalize(normal);
    };

    Triangle operator+(const glm::vec3& shift) {
        return Triangle(v1 + shift, v2 + shift, v3 + shift, normal);
    }
    Triangle operator-(const glm::vec3& shift) {
        return Triangle(v1 - shift, v2 - shift, v3 - shift, normal);
    }

    Triangle operator/(const glm::vec3& scale) {
        Triangle t = Triangle(v1 / scale, v2 / scale, v3 / scale, normal);
        t.normalize();
        return t;
    }
    Triangle operator*(const glm::vec3& scale) {
        Triangle t = Triangle(v1 * scale, v2 * scale, v3 * scale, normal);
        t.normalize();
        return t;
    }

    void normalize(){
        normal = glm::normalize(glm::cross(v2-v1,v3-v1));
    }

public:
    glm::vec3 v1, v2, v3;
    glm::vec3 normal;

};

class Mesh{
public:
    Mesh(const std::vector<float> &m_positions, const std::vector<float> &m_normals);
    Mesh(const std::vector<float> &m_positions, const std::vector<float> &m_normals, glm::vec3 m_pos);

public:
    glm::vec3 m_pos = glm::vec3(0,0,0);
    std::vector<std::shared_ptr<Triangle>> m_triangles;
};

#endif // MESH_H
