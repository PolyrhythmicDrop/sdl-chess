#include "ServiceLocator.h"
#include "easylogging++.h"

ServiceLocator::ServiceLocator()
{
	LOG(TRACE) << "Service Locator constructed!";
}

ServiceLocator::~ServiceLocator()
{
	LOG(TRACE) << "Service Locator destructed!";
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
		LOG(DEBUG) << "Loading null graphics service because Graphics Service failed to initialize. Check your code!";
	}
	else
	{
		// set the graphics service to the passed one
		_graphicsService = graphicsService;
	}
}
