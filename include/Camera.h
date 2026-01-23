#pragma once
#include "glm.hpp"

class Camera
{
public:

    Camera();
    void Update();
    void Set3dView();

protected:

    glm :: mat4 m_view;
    glm :: mat4 m_proj;
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;
};