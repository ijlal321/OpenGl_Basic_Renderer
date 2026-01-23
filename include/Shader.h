#pragma once
#include <string>
#include <glad/glad.h>
#include <glm.hpp>

class Shader
{

public:
    enum class ShaderType {VERTEX_SHADER, FRAGMENT_SHADER};    

public:
    
    static Shader* Instance();

public:

    bool CreateProgram();
    bool CreateShaders();

    GLuint GetShaderProgramID();

    bool CompileShaders(const std :: string& filename, ShaderType shaderType);
    void AttachShaders();
    bool LinkProgram();

    void DetachShaders();
    void DestroyShaders();
    void DestroyProgram();

    bool SendUniformData(const std :: string& uniformName, GLint data);
    bool SendUniformData(const std :: string& uniformName, GLuint data);
    bool SendUniformData(const std :: string& uniformName, GLfloat data);

    bool SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y);
    bool SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y, GLfloat z);
    bool SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    bool SendUniformData(const std :: string& uniformName, const glm::mat4& data);

private:

    Shader();
    Shader(const Shader&);
    Shader& operator=(Shader&);

private: 
    
    GLuint m_shaderProgramID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
    
};