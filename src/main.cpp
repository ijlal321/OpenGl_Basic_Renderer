// #include <windows.h>
// #include <gl/GL.h>
#include <glad/glad.h>
#include <SDL.h>
#include <iostream>

#include "Screen.h"
#include "Input.h"
#include "Shader.h"

bool isAppRunning = true;
Screen * screen = Screen::Instance();
Input * input = Input::Instance();
Shader * shader = Shader::Instance();


int main(int argc, char* argv[]){
    
    screen->Initialize();

    // =================================
    

    shader->CreateProgram();
    shader->CreateShaders();

    // Path relative to exe file.
    shader->CompileShaders("../../Shaders/Main.vert", Shader::ShaderType::VERTEX_SHADER);
    shader->CompileShaders("../../Shaders/Main.frag", Shader::ShaderType::FRAGMENT_SHADER);

    shader->AttachShaders();
    shader->LinkProgram();

    float x_pos = 0;
    float y_pos = 0;

    //=======================================

    //data that represents vertices for quad
    GLfloat vertices[] = { -0.5f,  0.5f,  0.0f,
                            0.5f,  0.5f,  0.0f,
                           -0.5f, -0.5f,  0.0f,     //triangle 1

                           -0.5f, -0.5f,  0.0f,
                            0.5f,  0.5f,  0.0f,
                            0.5f, -0.5f,  0.0f };   //triangle 2

    //data that represents colors for quad
    GLfloat colors[]={  1.0f,  0.0f,  0.0f,
                        0.0f,  0.0f,  1.0f,
                        0.0f,  1.0f,  1.0f,     //triangle 1
 
                        0.0f,  1.0f,  1.0f,
                        0.0f,  0.0f,  1.0f,
                        0.0f,  1.0f,  0.0f };      //triangle 2


    GLuint shaderProgramID = shader->GetShaderProgramID();

    GLint vertexID = glGetAttribLocation(shaderProgramID, "vertexIn");
    GLint colorID = glGetAttribLocation(shaderProgramID, "colorIn");

    GLuint vertexVBO;
    GLuint colorVBO;
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &colorVBO);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vertexID);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(colorID);

    while (isAppRunning){

        screen->ClearScreen();
        input->Update();

        // Processing Input - Separate function
        isAppRunning = !input->IsXClicked();
        if (input->IsKeyPressed()) {
            char key_pressed = input->GetKeyDown();
            if (key_pressed == SDLK_a){
                x_pos -= 0.001f;
            }
            else if (key_pressed == SDLK_d){
                x_pos += 0.001f;
            }
            else if (key_pressed == SDLK_s){
                y_pos -= 0.001f;
            }
            else if (key_pressed == SDLK_w){
                y_pos += 0.001f;
            }
            else if (key_pressed == SDLK_ESCAPE){
                isAppRunning = false;
            } 
        }


       glDrawArrays(GL_TRIANGLES, 0, 6);




        screen->Present();
        
    }
    
    // =================================

    shader->DetachShaders();
    shader->DestroyShaders();
    shader->DestroyProgram();

    screen->Shutdown();
    return 0;
}