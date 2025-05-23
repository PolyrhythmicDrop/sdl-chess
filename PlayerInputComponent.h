#pragma once
#include "InputComponent.h"
class PlayerInputComponent : public InputComponent
{

public:

	PlayerInputComponent();
	~PlayerInputComponent() {};

	InputComponent* getInputComponent();

	void handleInput(SDL_Event event);
	void onClick();
	void onHover();
	void onKeyPress();
};

