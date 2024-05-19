#pragma once
#include "InputComponent.h"

class PieceInputComponent :  public InputComponent
{
public:

	~PieceInputComponent() {};

	PieceInputComponent* getInputComponent();

	void handleInput(SDL_Event event);

	void onClick();
	void onHover();
	void onKeyPress();
	void onSelected();
};

