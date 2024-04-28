#pragma once
#include "Texture.h"

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
public:
	void virtual assignTexture(Texture* loader) = 0;
	void virtual draw() = 0;
};

