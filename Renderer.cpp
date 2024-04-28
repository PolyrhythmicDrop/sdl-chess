#include "GameContext.h"
#include "Renderer.h"

Renderer::Renderer()
{
	_renderer = NULL;
}

Renderer::~Renderer()
{
	std::cout << "Renderer destructed!";
}

void Renderer::SetRenderer()
{

}