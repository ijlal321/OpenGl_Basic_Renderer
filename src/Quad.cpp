#include "Quad.h"
#include "Shader.h"
#include "Input.h"
#include <SDL.h>
#include "gtc/matrix_transform.hpp"

Quad::Quad()
{
    //data that represents vertices for quad
    GLfloat vertices[] = { -0.5f,  0.5f,  0.0f,
                            0.5f,  0.5f,  0.0f,
                           -0.5f, -0.5f,  0.0f,     //triangle 1

                           -0.5f, -0.5f,  0.0f,
                            0.5f,  0.5f,  0.0f,
                            0.5f, -0.5f,  0.0f };   //triangle 2

    //data that represents colors for quad
    GLfloat colors[]={  0.0f,  0.0f,  1.0f,
                        0.0f,  0.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,     //triangle 1
 
                        1.0f,  1.0f,  1.0f,
                        0.0f,  0.0f,  1.0f,
                        1.0f,  1.0f,  1.0f };      //triangle 2

    
        m_buffer.CreateBuffer(6);
        m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
        m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);

        m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
        m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);

        m_position = glm::vec3(0,0,0); // make sure starting position is always 0,0,0
}

Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}

void Quad::render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    m_buffer.Render(Buffer::TRIANGLES);
}

void Quad::update()
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


    m_model = glm::mat4(1.0f); // Identity Matrix
    m_model = glm::translate(m_model, m_position);
    // m_model = glm::rotate(m_model, glm::radians(45.0f), glm::vec3(0, 0, 1));
    // m_model = glm::scale(m_model, glm::vec3(0.5f, 0.5f, 1.0f));
}
}
