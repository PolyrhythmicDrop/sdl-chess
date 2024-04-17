// Main game loop for SDL Chess

#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "SDLfunc.h"


// ** Main loop **

int main( int argc, char* args[] )
{
	SDLfunc sdlEngine{};
	sdlEngine.Init();
	sdlEngine.Close();


	return 0;
};