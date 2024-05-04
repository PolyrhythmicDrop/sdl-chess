#pragma once
#include "GameObject.h"
#include "IDrawable.h"
#include <SDL.h>
#include <stdio.h>
#include <functional>

class Decoration : public GameObject, public IDrawable
{
private:
	
	

public:

	const enum DecorationType
	{
		ESC_MENU_BG,
		RESO_MENU_BG
	};

	/// <summary>
	/// Construct the decoration, passing in the specific DecorationType that the decoration is.
	/// </summary>
	/// <param name="type">The type of decoration</param>
	Decoration(DecorationType type);

	~Decoration();	


};

