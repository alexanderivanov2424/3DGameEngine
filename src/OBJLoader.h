#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "engine/util/CommonIncludes.h"
#include <vector>

struct OBJData{
    std::vector<float> positions = std::vector<float>();
    std::vector<float> uvs =  std::vector<float>();
    std::vector<float> normals =  std::vector<float>();
};

class OBJLoader
{
public:
    OBJLoader();
    ~OBJLoader();
    static OBJData loadOBJ(const char *path);
};

#endif // OBJLOADER_H
