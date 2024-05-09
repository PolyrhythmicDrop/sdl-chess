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
	void handleInput(SDL_Event event, Button& button, IMenuState* state, SceneEscMenu* scene);

	void onClick();
	void onClick(Button& button);
	// Overload for the menu scene and menu buttons
	void onClick(Button& button, IMenuState* state, SceneEscMenu* scene);

	void onHover();
	void onKeyPress();
};

