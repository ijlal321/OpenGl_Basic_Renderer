// #include <windows.h>
// #include <gl/GL.h>
#include <glad/gl.h>
#include <SDL.h>
#include <iostream>

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Cube.h"

bool isAppRunning = true;
Screen * screen = Screen::Instance();
Input * input = Input::Instance();


int main(int argc, char* argv[]){
    
    screen->Initialize();

    // =================================
    
	Shader lightShader;
	lightShader.Create("../../Shaders/Main.vert", "../../Shaders/Main.frag");
	lightShader.Use();

	float xPos = 0.0f;
	float yPos = 0.0f;

	//================================================================

	Quad quad;
	Cube cube;
	Model model;
	model.Load("../../Models/Armchair.obj");

	Camera camera;
	camera.Set3DView();

	Light light;

    while (isAppRunning){

        screen->ClearScreen();
        input->Update();

        // Processing Input - Separate function
        isAppRunning = !input->IsXClicked();
        if (input->IsKeyPressed()) {
            char key_pressed = input->GetKeyDown();
            if (key_pressed == SDLK_ESCAPE){
                isAppRunning = false;
            } 
        }
        camera.Update();
		camera.SendToShader(lightShader);

        light.Update();
		light.Render(lightShader);
		light.SendToShader(lightShader);

        light.Update();    
        light.Render(lightShader);
        light.SendToShader(lightShader);

		//quad.Update();
		//quad.Render(lightShader);

		//cube.Update();
		//cube.Render(lightShader);

		model.Update();
		model.Render(lightShader);
        
        screen->Present();
        
    }
    
    // =================================

    lightShader.Destroy();	

    screen->Shutdown();
    return 0;
}