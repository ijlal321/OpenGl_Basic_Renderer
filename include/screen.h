#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <SDL.h>

class Screen {

public:

    static Screen * Instance();
    
private:
    
    SDL_Window* window;
    SDL_GLContext context;
    
private:
    
    Screen();
    Screen(const Screen&);
    Screen& operator=(const Screen&);

public:

    bool Initialize();
    void ClearScreen();
    void Present();
    void Shutdown();


};