#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"

class Decoration : public GameObject
{
private:

	std::unique_ptr<GraphicsComponent> _graphics;

public:

	const enum DecorationType
	{
		ESC_MENU_BG,
		RESO_MENU_BG,
		EXIT_CONFIRM_BG
	};

	/// <summary>
	/// Construct the decoration, passing in the specific DecorationType that the decoration is.
	/// </summary>
	/// <param name="type">The type of decoration</param>
	Decoration(DecorationType type);

	~Decoration();

	GraphicsComponent* getGraphicsComponent();

};

