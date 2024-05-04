#pragma once
#include "Window.h"
#include "Renderer.h"
#include "GameObject.h"
#include <vector>

// Pure abstract class for graphics handling, should be inherited by both the NullGraphicsService and the GraphicsService.
class IGraphics
{
		

public:

	~IGraphics() {};

	virtual Window* getWindow() = 0;

	virtual Renderer* getRenderer() = 0;

	virtual void addToQueue(std::vector<GameObject*>) = 0;

	virtual void removeFromQueue() = 0;

	virtual void render() = 0;

	};

