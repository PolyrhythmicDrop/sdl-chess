#include "DrawManager.h"

DrawManager::DrawManager(Renderer* renderer) :
	_renderer(renderer)
{
	std::cout << "Draw Manager initialized!\n";
}

DrawManager::~DrawManager()
{
	std::cout << "Draw Manager destructed!\n";
}

void DrawManager::drawQueue()
{

}
