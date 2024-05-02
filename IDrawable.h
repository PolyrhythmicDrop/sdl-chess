#pragma once
#include "Texture.h"
#include "GraphicsService.h"
#include <SDL.h>
#include <SDL_image.h>

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
protected:
	Texture* _texture;
	std::string _imgPath;

public:

	IDrawable(std::string path);
	~IDrawable();
	void virtual loadTexture();
	void virtual addToDrawQueue();
};

