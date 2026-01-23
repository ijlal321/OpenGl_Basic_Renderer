#pragma once
#include <glad/glad.h>
#include "Buffer.h"

class Quad
{

public:
    Quad();
    ~Quad();

    void render();

private:
    Buffer m_buffer;

};