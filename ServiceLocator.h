#pragma once
#include "IGraphics.h"
#include "NullGraphicsService.h"

class ServiceLocator
{
private:
	static IGraphics* _graphicsService;
	static NullGraphicsService _nullGraphicsService;

public:
	ServiceLocator();
	~ServiceLocator();

	static void initialize();

	static IGraphics& getGraphics();

	static void provide(IGraphics* graphicsService);

};

