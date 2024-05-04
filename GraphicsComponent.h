#pragma once
#include "IDrawable.h"
#include "Texture.h"

class GraphicsComponent: public IDrawable
{
private:
	Texture* _textureLoader;
	SDL_Texture* _sdlTexture;
	std::string _imgPath;
	// Z-index for drawing purposes. Higher values render on top of lower values.
	int _zIndex;

public:
	
	GraphicsComponent();

	~GraphicsComponent();

	void setImgPath(std::string path);

	void loadTexture();

	SDL_Texture* getSdlTexture();

	GraphicsComponent* getGraphicsComponent();

	int getZ();

	void setZ(int z);

};

