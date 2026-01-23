#include "Camera.h"
#include "Shader.h"
#include "Input.h"
#include <SDL.h>
#include <gtc/matrix_transform.hpp>

Camera::Camera()
{
    m_view = glm::mat4(1.0f);
    m_proj = glm::mat4(1.0f);
    m_position = glm::vec3(0.f);
    m_direction = glm::vec3(0.f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::Update()
{
     if (Input::Instance()->IsKeyPressed()) {
        char key_pressed = Input::Instance()->GetKeyDown();
        if (key_pressed == SDLK_a){
            m_position.x -= 0.001f;
        }
        else if (key_pressed == SDLK_d){
            m_position.x += 0.001f;
        }
        else if (key_pressed == SDLK_s){
            m_position.y -= 0.001f;
        }
        else if (key_pressed == SDLK_w){
            m_position.y += 0.001f;
        }
        else if (key_pressed == SDLK_q){
            m_position.z -= 0.001f;
        }
        else if (key_pressed == SDLK_e){
            m_position.z += 0.001f;
        }
    }

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
    Shader::Instance()->SendUniformData("view", m_view);
}

void Camera::Set3dView()
{
    GLfloat FOV = 45.0f;
    GLfloat aspectRatio = 1280.0f / 720.0f;

    m_proj = glm :: perspective(FOV, aspectRatio, 0.001f, 1000.0f);
    Shader::Instance()->SendUniformData("proj", m_proj);
}
