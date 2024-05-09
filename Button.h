#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"

class ButtonInputComponent;

class Button : public GameObject
{
private:
	GraphicsComponent* _graphics;
	ButtonInputComponent* _input;

public:

	const enum ButtonType {
		OPTIONS,
		BACK,
		EXITGAME,
		RESOLUTION,
		YES,
		NO
	};

	Button(ButtonType type);
	~Button();

	ButtonType type;

	GraphicsComponent* getGraphicsComponent();
	ButtonInputComponent* getInputComponent();


};

