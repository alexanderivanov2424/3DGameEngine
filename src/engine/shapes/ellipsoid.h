#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "engine/util/CommonIncludes.h"

class Ellipsoid{
public:
    Ellipsoid(glm::vec3 radii);
    Ellipsoid(glm::vec3 translation, glm::vec3 radii);

public:
    glm::vec3 m_pos;
    glm::vec3 m_radii;
};

#endif // ELLIPSOID_H
