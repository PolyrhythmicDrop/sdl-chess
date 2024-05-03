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
	Texture* _textureLoader;
	SDL_Texture* _sdlTexture;
	std::string _imgPath;

public:

	IDrawable(std::string path);
	~IDrawable();
	virtual void loadTexture();
	virtual SDL_Texture* getSdlTexture();
	virtual void addToDrawQueue();
	virtual void draw(int x, int y, int w, int h);
};

