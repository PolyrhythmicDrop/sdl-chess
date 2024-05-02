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

}

void IDrawable::addToDrawQueue()
{}