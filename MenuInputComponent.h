#pragma once
#include "InputComponent.h"

class MenuInputComponent : public InputComponent
{
public:

	MenuInputComponent() {};
	~MenuInputComponent() {};

	InputComponent* getInputComponent();

	void handleInput(SDL_Event event);
	void onClick();
	void onHover();
	void onKeyPress();
};

