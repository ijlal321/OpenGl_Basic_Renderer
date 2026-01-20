#include <windows.h>
#include <SDL.h>
#include <gl/GL.h>
#include <iostream>

#include "screen.h"

bool isAppRunning = true;
Screen * screen = Screen::Instance();


int main(int argc, char* argv[]){
    
    screen->Initialize();

    // =================================
    
    while (isAppRunning){

        screen->ClearScreen();

//render a quad the OLD way
glBegin(GL_QUADS);

//top left color and vertex of quad
glColor3f(1, 0,0);
glVertex3f(-0.5f, 0.5f, 0.0f);

//top right color and vertex of quad
glColor3f(0,1,0);
glVertex3f(0.5f,0.5f,0.0f);

//bottom right color and vertex of quad
glColor3f(0,0,1);
glVertex3f(0.5f, -0.5f,0.0f);

//bottom left color and vertex of quad
glColor3f(0,0,1);
glVertex3f(-0.5f, -0.5f,0.0f);

glEnd();




        screen->Present();
        
    }
    
    // =================================

    screen->Shutdown();
    return 0;
}