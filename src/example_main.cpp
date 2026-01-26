// #include <windows.h>
// #include <gl/GL.h>
#include <glad/glad.h>
#include <SDL.h>
#include <iostream>

bool isAppRunning = true;

SDL_Window * window;
SDL_GLContext context;

bool initialize_Screen()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << "Cannot Init SDL" << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    window = SDL_CreateWindow("Graphics Engine", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        1280, 720, SDL_WINDOW_OPENGL
    );

    if (!window){
        std::cout << "Error creating SDL window" << std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);

    if (!context){
        std::cout << "Error creating OpenGL Ontext." << std :: endl;
        return false;
    }

    if (!gladLoadGL()){
        std::cout << "Error loading Glad Extensions for Opengl." << std :: endl;
        return false;
    }

    return true;
}

bool Compile_and_Link_Shaders(GLuint shader_id, const char * source_code){
    
    // 1. Bind shader source code with shader id.
    glShaderSource(shader_id, 1, &source_code, nullptr);
    // 2. compiler shader itself
    glCompileShader(shader_id);

    // check for errors
    // not doing

        GLint error_code;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &error_code);

        if (error_code != GL_TRUE){
            std::cout << "Error COmpiling Shader file." << std::endl;
            
            GLchar error_message[1000];
            GLsizei buffer_szie = 1000;

            glGetShaderInfoLog(shader_id, buffer_szie, &buffer_szie, error_message);

            std::cout << error_message << std::endl;
            return false;
        }

        return true;
}

bool load_compile_and_link_shaders(GLuint m_shaderProgramID,GLuint m_vertexShaderID,GLuint m_fragmentShaderID){
    Compile_and_Link_Shaders(m_vertexShaderID, R"(#version 460 
    in vec3 vertexIn;
    in vec3 colorIn;
    out vec3 colorOut;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

    void main(){
        colorOut = colorIn;
        // order of multiuplication is reverse. from right to left. view is in last, as needed.
        gl_Position = vec4(vertexIn, 1.0);
    })");

    Compile_and_Link_Shaders(m_fragmentShaderID, R"(
    #version 460

    in vec3 colorOut;
    out vec4 fragColor;
    
    void main(){
        fragColor = vec4(colorOut, 1.0);
    })");

    // attach shaders
    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);

    // link shaders
    glLinkProgram(m_shaderProgramID);
    glUseProgram(m_shaderProgramID);
    // check for linking errors
    GLint error_code;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &error_code);
    if (error_code != GL_TRUE){
        std::cout << "Error Linking Shaders." << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]){
    if (! initialize_Screen())
        return 0;

    // Create prgorams and shaders (container and Id)
    GLuint m_shaderProgramID = glCreateProgram();  // create program 
    GLuint m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);  // create shaders (vertex)
    GLuint m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);  // create shaders (fragment)
    
    if (!load_compile_and_link_shaders(m_shaderProgramID, m_vertexShaderID, m_fragmentShaderID)){
        return 0;
    }

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

    GLuint m_VAO;
    GLuint m_vertexVBO;
    GLuint m_colorVBO;

    glGenBuffers(1, &m_vertexVBO);
    glGenBuffers(1, &m_colorVBO);
    glGenVertexArrays(1, &m_VAO);

    glBindVertexArray(m_VAO);

        // binding vertices
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // set buffer to data
        GLint ID = glGetAttribLocation(m_shaderProgramID, "vertexIn");
        glVertexAttribPointer(ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // explain how tp interpret data
                    //           3 -> meaning take 3 at a time. for x,y,z. 
        glEnableVertexAttribArray(ID);
        
        // binding color
        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        ID = glGetAttribLocation(m_shaderProgramID, "colorIn");
        glVertexAttribPointer(ID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(ID);


    glBindVertexArray(0);

    //=======================================

    while (isAppRunning){

        // Clear Screen
        glClear(GL_COLOR_BUFFER_BIT);

        // process inputs
        SDL_Event events;
        while (SDL_PollEvent(&events)){}

        // render;
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); // start from 0. draw 6 vertices
        glBindVertexArray(0);

        // show screen
        SDL_GL_SwapWindow(window);
        
    }
    
    // =================================

    // shader->DetachShaders();
    // shader->DestroyShaders();
    // shader->DestroyProgram();

    // screen->Shutdown();
    return 0;
}