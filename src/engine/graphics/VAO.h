#ifndef VAO_H
#define VAO_H

#include <vector>
#include <memory>

#include "GL/glew.h"

class VBO;
class IBO;

class VAO {
public:
    VAO(const VBO &vbo, int numberOfVerticesToRender = 0);
    VAO(const VBO &vbo, const IBO &ibo, int numberOfVerticesToRender = 0);
    VAO(std::vector<VBO> &vbos, int numberOfVerticesToRender = 0);
    VAO(std::vector<VBO> &vbos, const IBO &ibo, int numberOfElementsToRender = 0);
    VAO(const VAO &that) = delete;
    VAO& operator=(const VAO &that) = delete;
    VAO(VAO &&that);
    VAO& operator=(VAO &&that);
    ~VAO();

    enum DRAW_METHOD { DRAW_ARRAYS, DRAW_INDEXED };

    void bind();
    void draw();
    void draw(int count);
    DRAW_METHOD drawMethod();
    void unbind();

private:
    DRAW_METHOD m_drawMethod;
    GLuint m_handle;
    GLuint m_numVertices; // this is actually the number of faces to render if this VAO uses an IBO
    int m_size;
    GLenum m_triangleLayout;
};

#endif // VAO_H
