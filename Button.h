#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"



class Button: public GameObject
{
private:
	GraphicsComponent* _graphics;
	InputComponent* _input;

public:

	const enum ButtonType {
		OPTIONS,
		BACK,
		EXIT_GAME,
		RESOLUTION
	};

	// Constructors
	Button(ButtonType type);

	~Button();

	ButtonType type;

	GraphicsComponent* getGraphicsComponent();
	InputComponent* getInputComponent();


};

