#pragma once
#include "glad/glad.h"
class Quad
{

public:
    Quad();
    ~Quad();

    void render();

private:

    GLuint m_VAO;
    GLuint m_vertexVBO;
    GLuint m_colorVBO;
    GLint m_colorID;
    GLint m_vertexID;
};