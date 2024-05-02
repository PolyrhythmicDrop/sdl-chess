#include "Decoration.h"

Decoration::Decoration(std::string name, std::string path) :
	GameObject::GameObject(name), IDrawable::IDrawable(path)
{
	std::cout << "Decoration " << _name << " created!\n";
}

Decoration::~Decoration()
{
	std::cout << _name << " destructed!\n";
}

void Decoration::loadTexture()
{
	_sdlTexture = _textureLoader->loadTextureFromImage(_imgPath);
	std::cout << "Texture loaded to " << _name << "!\n";
}

void Decoration::addToDrawQueue()
{
	
}

void Decoration::draw(int x, int y)
{
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	SDL_Rect destRect = { _dimensions.w, _dimensions.h, x, y };
	SDL_Rect srcRect = { _dimensions.w, _dimensions.h, _dimensions.x, _dimensions.y };
	SDL_RenderCopy(renderer, _sdlTexture, &srcRect, &destRect);
}



