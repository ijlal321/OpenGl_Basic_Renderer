#include "Light.h"
#include "Shader.h"
#include "Input.h"
#include <SDL.h>
#include "gtc/matrix_transform.hpp"


Light::Light()
{
    m_ambient = glm :: vec3(1.0f);
    m_diffuse = glm :: vec3(1.0f);
    m_specular = glm :: vec3(1.0f);
    m_position = glm :: vec3(0.0f, 1.0f, 0.0f);

    GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
    GLfloat colors[] = { 1.0f, 1.0f, 1.0f };

    m_buffer.CreateBuffer(1);

    m_buffer.FillVBO(Buffer::VBOType::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::COLOR_BUFFER, colors, sizeof(colors), Buffer::FillType::Once);

    m_buffer.LinkBuffer("vertexIn", Buffer :: Buffer::VBOType::VERTEX_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
    m_buffer.LinkBuffer("colorIn", Buffer :: Buffer::VBOType::COLOR_BUFFER, Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);
}

Light::~Light()
{
    m_buffer.DestroyBuffer();
}

void Light::Update()
{
    if (Input::Instance()->IsKeyPressed()) {
        char key_pressed = Input::Instance()->GetKeyDown();
        if (key_pressed == SDLK_j){
            m_position.x -= 0.001f;
        }
        else if (key_pressed == SDLK_l){
            m_position.x += 0.001f;
        }
        else if (key_pressed == SDLK_k){
            m_position.y -= 0.001f;
        }
        else if (key_pressed == SDLK_i){
            m_position.y += 0.001f;
        }
        else if (key_pressed == SDLK_u){
            m_position.z -= 0.001f;
        }
        else if (key_pressed == SDLK_o){
            m_position.z += 0.001f;
        }
    }
    m_model = glm::mat4(1.0f); // Identity Matrix
    m_model = glm::translate(m_model, m_position);

}

// See the actual light bulb [useful in debug mode only ]
void Light::Render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    Shader::Instance()->SendUniformData("isLit", false);
    Shader::Instance()->SendUniformData("isTextured", false);

    glPointSize(20.0f);
    m_buffer.Render(Buffer::DrawType::POINTS);
}

void Light::SendToShader()
{
    Shader::Instance()->SendUniformData("light.position", m_position.x, m_position.y, m_position.z);
    Shader::Instance()->SendUniformData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
    Shader::Instance()->SendUniformData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
    Shader::Instance()->SendUniformData("light.specular", m_specular.r, m_specular.g, m_specular.b);
}
