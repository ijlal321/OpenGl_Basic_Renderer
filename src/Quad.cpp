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
    GLfloat colors[]={  1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,     //triangle 1
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f };      //triangle 2

    //data that represents UV coordinates for quad
    GLfloat UVs[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f, //triangle 1

        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f  //triangle 2
        }; 
    
    m_buffer.CreateBuffer(6);
    m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
    m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);
    m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::SINGLE);

    m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
    m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);
    m_buffer.LinkBuffer("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);

    m_texture.Load("../../Textures/crate_1.png");

    m_position = glm::vec3(0,0,0); 
    m_shininess = 50.0f;
    m_ambient = glm :: vec3(0.4f, 0.4f, 0.4f);
    m_diffuse = glm :: vec3(0.1f, 0.7f, 0.2f);
    m_specular = glm :: vec3(0.8f, 0.8f, 0.8f);

}

Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}

void Quad::render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    Shader::Instance()->SendUniformData("isLit", true);
    Shader::Instance()->SendUniformData("isTextured", true);

    Shader::Instance()->SendUniformData("material.shininess", m_shininess);
    Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
    Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
    Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);

    m_texture.Bind();
    m_buffer.Render(Buffer :: TRIANGLES);
    m_texture.Unbind();
}

void Quad::update()
{
    // if (Input::Instance()->IsKeyPressed()) {
    //     char key_pressed = Input::Instance()->GetKeyDown();
    //     if (key_pressed == SDLK_j){
    //         m_position.x -= 0.001f;
    //     }
    //     else if (key_pressed == SDLK_l){
    //         m_position.x += 0.001f;
    //     }
    //     else if (key_pressed == SDLK_k){
    //         m_position.y -= 0.001f;
    //     }
    //     else if (key_pressed == SDLK_i){
    //         m_position.y += 0.001f;
    //     }
    //     else if (key_pressed == SDLK_u){
    //         m_position.z -= 0.001f;
    //     }
    //     else if (key_pressed == SDLK_o){
    //         m_position.z += 0.001f;
    //     }
    // }


    m_model = glm::mat4(1.0f); // Identity Matrix
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // m_model = glm::scale(m_model, glm::vec3(0.5f, 0.5f, 1.0f));

}
