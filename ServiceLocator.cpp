#include "ServiceLocator.h"
#include "easylogging++.h"

ServiceLocator::ServiceLocator()
{
	LOG(INFO) << "Service Locator constructed!\n";
}

ServiceLocator::~ServiceLocator()
{
	LOG(INFO) << "Service Locator destructed!\n";
}

void ServiceLocator::initialize()
{
	// Initialize to null service until a real graphics service is provided.
	_graphicsService = &_nullGraphicsService;
}

IGraphics& ServiceLocator::getGraphics()
{
	// Return the graphics service
	return *_graphicsService;
}

void ServiceLocator::provide(IGraphics* graphicsService)
{
	if (_graphicsService == NULL)
	{
		// Revert to the null service
		_graphicsService = &_nullGraphicsService;
		LOG(INFO) << "Loading null graphics service! Check your code.";
	}
	else
	{
		// set the graphics service to the passed one
		_graphicsService = graphicsService;
	}
}
