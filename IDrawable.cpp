#include "IDrawable.h"

IDrawable::IDrawable(std::string path) :
	_imgPath(path), _textureLoader(NULL), _sdlTexture(NULL)
{
	_textureLoader = new Texture();
}

IDrawable::~IDrawable()
{
	_textureLoader->~Texture();
}

void IDrawable::loadTexture()
{
	_sdlTexture = _textureLoader->loadTextureFromImage(_imgPath);
}

SDL_Texture* IDrawable::getSdlTexture()
{
	return _sdlTexture;
}

void IDrawable::addToDrawQueue()
{
}

void IDrawable::draw(int x, int y, int w, int h)
{
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	SDL_Rect destRect = { x, y, w, h };
	SDL_RenderCopy(renderer, _sdlTexture, NULL, &destRect);
}