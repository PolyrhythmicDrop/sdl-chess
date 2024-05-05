#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <stdio.h>
#include <string>

class Button: public GameObject
{
private:
	GraphicsComponent* _graphics;

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

	GraphicsComponent* getGraphicsComponent();


};

