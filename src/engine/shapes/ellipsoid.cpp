#include "ellipsoid.h"

Ellipsoid::Ellipsoid(glm::vec3 radii){
    m_pos = glm::vec3(0,0,0);
    m_radii = radii;
}

Ellipsoid::Ellipsoid(glm::vec3 m_pos, glm::vec3 radii){
    m_pos = m_pos;
    m_radii = radii;
}
