#pragma once
#include "IGraphics.h"

// Null Graphics service so the service locator doesn't return NULL and crash the game
class NullGraphicsService : public IGraphics
{
public:		

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs);

	virtual void removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects);

	virtual void render();
};

