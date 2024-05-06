#pragma once
#include "SDLfunc.h"


// Input Component interface
class InputComponent
{

public:
	
	virtual ~InputComponent() {};

	virtual InputComponent* getInputComponent() = 0;

	virtual void handleInput(SDL_Event event) = 0;
	virtual void onClick() = 0;
	virtual void onHover() = 0;
	virtual void onKeyPress() = 0;
};

