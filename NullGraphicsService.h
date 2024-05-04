#pragma once
#include "IGraphics.h"

// Null Graphics service so the service locator doesn't return NULL and crash the game
class NullGraphicsService : public IGraphics
{
public:		

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToRenderMap(std::map<GameObject*, SDL_Texture*> map);

	virtual void removeFromQueue();

	virtual void render();
};

