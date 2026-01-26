#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include "Buffer.h"
#include "Texture.h"

class Quad
{

public:
    Quad();
    ~Quad();

    void render();
    void update();

private:
    Buffer m_buffer;
    Texture m_texture;
    glm::mat4 m_model;
    glm::vec3 m_position;
};