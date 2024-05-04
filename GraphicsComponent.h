#pragma once
#include "IDrawable.h"
#include "Texture.h"

class GraphicsComponent: public IDrawable
{
private:
	Texture* _textureLoader;
	SDL_Texture* _sdlTexture;

public:
	std::string _imgPath;


	GraphicsComponent();

	~GraphicsComponent();

	void loadTexture();

	SDL_Texture* getSdlTexture();

	GraphicsComponent* getGraphicsComponent();

};

