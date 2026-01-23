#include "Shader.h"
#include <iostream>
#include <fstream>

Shader *Shader::Instance()
{
    static Shader * shader_program = new Shader();
    return shader_program;
}


Shader::Shader(){
    m_fragmentShaderID = 0;
    m_shaderProgramID = 0;
    m_vertexShaderID = 0;
}

bool Shader::CreateProgram()
{
    m_shaderProgramID = glCreateProgram();
    if (m_shaderProgramID == 0){
        std::cout << "Error creating Shader program" << std::endl;
        return false;
    }
    return true;
}

bool Shader::CreateShaders()
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0){
        std::cout << "Error creating Vertex Shader object" << std::endl;
        return false;
    }
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0){
        std::cout << "Error creating Framgment Shader object" << std::endl;
        return false;
    }
    return true;
}

GLuint Shader::GetShaderProgramID()
{
    return m_shaderProgramID;
}

bool Shader::CompileShaders(const std::string &filename, ShaderType shaderType)
{
    std::fstream file;
    std::string text;
    std::string source_code;
    GLint shaderId;

    shaderId = (shaderType == ShaderType::VERTEX_SHADER) ? m_vertexShaderID : m_fragmentShaderID;

    file.open(filename);

    if (!file){
        std::cout << "Error Reading Shader File" << std::endl;
        return false;
    }

    while(!file.eof()){
        std::getline(file, text);
        source_code += text + "\n";
    }

    file.close();

    // Opengl needs a c style string
    const GLchar * final_source_code = source_code.c_str();

    // 1. Bind shader source code with shader id.
    glShaderSource(shaderId, 1, &final_source_code, nullptr);
    // 2. compiler shader itself
    glCompileShader(shaderId);

    GLint error_code;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &error_code);

    if (error_code != GL_TRUE){
        std::cout << "Error COmpiling Shader file." << std::endl;
        
        GLchar error_message[1000];
        GLsizei buffer_szie = 1000;

        glGetShaderInfoLog(shaderId, buffer_szie, &buffer_szie, error_message);

        std::cout << error_message << std::endl;
        return false;
    }

    return true;
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderProgramID);

    glUseProgram(m_shaderProgramID);

    GLint error_code;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &error_code);

    if (error_code != GL_TRUE){
        std::cout << "Error Linking Shaders." << std::endl;
        
        GLchar error_message[1000];
        GLsizei buffer_szie = 1000;

        glGetShaderInfoLog(m_shaderProgramID, buffer_szie, &buffer_szie, error_message);

        std::cout << error_message << std::endl;
        return false;
    }


    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_shaderProgramID, m_vertexShaderID);
    glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::AttachShaders()
{
    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderProgramID);
}


bool Shader::SendUniformData(const std :: string& uniformName, GLint data){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform1i(ID, data);
    return true;
}

bool Shader::SendUniformData(const std :: string& uniformName, GLuint data){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform1ui(ID, data);
    return true;
}

bool Shader::SendUniformData(const std :: string& uniformName, GLfloat data){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform1f(ID, data);
    return true;
}


bool Shader::SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform2f(ID, x, y);
    return true;
}

bool Shader::SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y, GLfloat z){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform3i(ID, x, y, z);
    return true;
}

bool Shader::SendUniformData(const std :: string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

    if (ID == -1){
        std::cout << "Shader variable " << uniformName << " not found or not used." << std :: endl;
        return false;
    }
    glUniform4i(ID, x, y, z, w);
    return true;
}
