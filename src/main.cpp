// #include <windows.h>
// #include <gl/GL.h>
#include <glad/glad.h>
#include <SDL.h>
#include <iostream>

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"

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
    Quad quad;
    

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
        quad.render();
        screen->Present();
        
    }
    
    // =================================

    shader->DetachShaders();
    shader->DestroyShaders();
    shader->DestroyProgram();

    screen->Shutdown();
    return 0;
}