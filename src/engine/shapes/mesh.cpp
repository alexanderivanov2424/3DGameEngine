#include "mesh.h"

Mesh::Mesh(const std::vector<float> &m_positions, const std::vector<float> &m_normals){
    for(int i = 0; i < m_positions.size(); i+= 9){
        glm::vec3 v1 = glm::vec3(m_positions[i], m_positions[i+1], m_positions[i+2]);
        glm::vec3 v2 = glm::vec3(m_positions[i+3], m_positions[i+4], m_positions[i+5]);
        glm::vec3 v3 = glm::vec3(m_positions[i+6], m_positions[i+7], m_positions[i+8]);
        glm::vec3 normal = glm::vec3(m_normals[i], m_normals[i+1], m_normals[i+2]);

        m_triangles.push_back(Triangle(v1,v2,v3,normal));
    }
}

Mesh::Mesh(const std::vector<float> &m_positions, const std::vector<float> &m_normals, glm::vec3 m_pos){
    this->m_pos = m_pos;
    for(int i = 0; i < m_positions.size(); i+= 9){
        glm::vec3 v1 = glm::vec3(m_positions[i], m_positions[i+1], m_positions[i+2]);
        glm::vec3 v2 = glm::vec3(m_positions[i+3], m_positions[i+4], m_positions[i+5]);
        glm::vec3 v3 = glm::vec3(m_positions[i+6], m_positions[i+7], m_positions[i+8]);
        glm::vec3 normal = glm::vec3(m_normals[i], m_normals[i+1], m_normals[i+2]);

        m_triangles.push_back(Triangle(v1,v2,v3,normal));
    }
}
