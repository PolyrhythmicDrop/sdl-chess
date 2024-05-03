#pragma once
#include "Texture.h"
#include "GameObject.h"
#include "IDrawable.h"
#include "IClickable.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include <iostream>

class Button: public GameObject, public IDrawable, public IClickable
{
private:		

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

	

	void virtual onClick();


};

