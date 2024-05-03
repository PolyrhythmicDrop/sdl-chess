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
	int w;
	int h;
	// Query loaded texture to get the width and height of the texture and set them to w & h variables
	SDL_QueryTexture(_sdlTexture, NULL, NULL, &w, &h);
	_dimensions.w = w;
	_dimensions.h = h;

	std::cout << "Texture loaded to " << _name << "!\n";
	std::cout << "Texture dimensions:\nW: " << _dimensions.w << " H: " << _dimensions.h << " X: " << _dimensions.x << " Y: " << _dimensions.y;
}

void Decoration::addToDrawQueue()
{
	
}

void Decoration::draw(int x, int y)
{
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	SDL_Rect destRect = { x, y, _dimensions.w, _dimensions.h };
	SDL_Rect srcRect = { _dimensions.x, _dimensions.y, _dimensions.w, _dimensions.h };
	SDL_RenderCopy(renderer, _sdlTexture, NULL, &destRect);
}



