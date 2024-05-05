#pragma once
#include "GameContext.h"
#include "Renderer.h"
#include <map>

// Pure abstract class for graphics handling, should be inherited by both the NullGraphicsService and the GraphicsService.
class IGraphics
{	

public:
	

	~IGraphics() {};

	virtual Window* getWindow() = 0;

	virtual Renderer* getRenderer() = 0;

	virtual void addToRenderMap(std::map<int, std::pair<GameObject*, SDL_Texture*>> map) = 0;

	virtual void removeFromQueue() = 0;

	virtual void render() = 0;

	};

