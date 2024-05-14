#pragma once
#include "GameContext.h"
#include "Renderer.h"
#include <map>

// Pure abstract class for graphics handling, should be inherited by both the NullGraphicsService and the GraphicsService.
class IGraphics
{	

public:
	enum Layer {
		BG,
		BOARD,
		PIECES,
		UI,
		MENU
	};

	~IGraphics() {};

	virtual Window* getWindow() = 0;

	virtual Renderer* getRenderer() = 0;

	virtual void addToRenderMap(std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> map) = 0;

	virtual void removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects) = 0;

	virtual void render() = 0;

	};

