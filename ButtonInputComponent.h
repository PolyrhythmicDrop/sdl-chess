#pragma once
#include "InputComponent.h"
#include "IMenuState.h"

class ButtonInputComponent : public InputComponent
{
public:

	ButtonInputComponent() {};
	~ButtonInputComponent() {};

	InputComponent* getInputComponent();

	void handleInput(SDL_Event event);
	void onClick();
	void onHover();
	void onKeyPress();
};

