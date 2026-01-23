#include "Quad.h"
#include "Shader.h"

Quad::Quad()
{
    //data that represents vertices for quad
    GLfloat vertices[] = { -1.0f,  1.0f,  0.0f,
                            1.0f,  1.0f,  0.0f,
                           -1.0f, -1.0f,  0.0f,     //triangle 1

                           -1.0f, -1.0f,  0.0f,
                            1.0f,  1.0f,  0.0f,
                            1.0f, -1.0f,  0.0f };   //triangle 2

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

}

Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}

void Quad::render()
{
    m_buffer.Render(Buffer::TRIANGLES);
}
