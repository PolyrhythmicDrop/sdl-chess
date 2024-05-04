#pragma once
#include <SDL.h>
#include <SDL_image.h>

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
protected:
	

public:

	virtual ~IDrawable() {};
	virtual void loadTexture() = 0;
	virtual SDL_Texture* getSdlTexture() = 0;
};

