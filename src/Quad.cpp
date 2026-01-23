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

    GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();

    m_vertexID = glGetAttribLocation(shaderProgramID, "vertexIn");
    m_colorID = glGetAttribLocation(shaderProgramID, "colorIn");


    glGenBuffers(1, &m_vertexVBO);
    glGenBuffers(1, &m_colorVBO);


    glGenVertexArrays(1, &m_VAO);

    
    glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(m_vertexID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(m_vertexID);

        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(m_colorID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(m_colorID);

    glBindVertexArray(0);

}

Quad::~Quad()
{
    glDeleteBuffers(1, &m_vertexVBO);
    glDeleteBuffers(1, &m_colorVBO);
    glDeleteVertexArrays(1, &m_VAO);

    glDisableVertexAttribArray(m_vertexID);
    glDisableVertexAttribArray(m_colorID);
}

void Quad::render()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
