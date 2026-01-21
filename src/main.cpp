#include <windows.h>
#include <SDL.h>
#include <gl/GL.h>
#include <iostream>

#include "Screen.h"
#include "Input.h"

bool isAppRunning = true;
Screen * screen = Screen::Instance();
Input * input = Input::Instance();


int main(int argc, char* argv[]){
    
    screen->Initialize();

    // =================================
    
    float x_pos = 0;
    float y_pos = 0;

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


        //render a quad the OLD way
        glBegin(GL_QUADS);

            //top left color and vertex of quad
            glColor3f(1, 0,0);
            glVertex3f(x_pos - 0.5f, y_pos + 0.5f, 0.0f);

            //top right color and vertex of quad
            glColor3f(0,1,0);
            glVertex3f(x_pos + 0.5f, y_pos + 0.5f, 0.0f);

            //bottom right color and vertex of quad
            glColor3f(0,0,1);
            glVertex3f(x_pos + 0.5f, y_pos  - 0.5f, 0.0f);

            //bottom left color and vertex of quad
            glColor3f(0,0,1);
            glVertex3f(x_pos - 0.5f, y_pos  - 0.5f, 0.0f);

        glEnd();




        screen->Present();
        
    }
    
    // =================================

    screen->Shutdown();
    return 0;
}