#pragma once
#include "InputComponent.h"
class ButtonInputComponent : public InputComponent
{
	ButtonInputComponent() {};
	~ButtonInputComponent() {};

	InputComponent* getInputComponent();

	void handleInput(SDL_Event event);
	void onClick();
	void onHover();
	void onKeyPress();
};

