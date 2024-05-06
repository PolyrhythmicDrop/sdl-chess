#pragma once
#include "IClickable.h"
#include "SDLfunc.h"

class InputComponent : public IClickable
{

public:
	InputComponent() {};
	~InputComponent() {};

	InputComponent* getInputComponent();

	void handleInput(SDL_Event event);
	void onClick();
	void onHover();
};

