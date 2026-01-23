#pragma once
#include <glad/glad.h>
#include "Buffer.h"
#include <glm.hpp>

class Quad
{

public:
    Quad();
    ~Quad();

    void render();
    void update();

private:
    Buffer m_buffer;
    glm::mat4 m_model;
    glm::vec3 m_position;
};