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

	// Button type. When adding a new button type, add it to the end of the enum. Edit the Button constructor, as well as the onClick function appropriately. DO NOT reorganize the list!
	const enum ButtonType {
		OPTIONS,
		BACK,
		EXITGAME,
		YES,
		NO,
		RESOLUTION,
		TENTWENTYFOUR,
		NINETEENTWENTY
	};

	Button(ButtonType type);
	~Button();

	ButtonType type;

	GraphicsComponent* getGraphicsComponent();
	ButtonInputComponent* getInputComponent();


};

