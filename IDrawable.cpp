#include "IDrawable.h"

IDrawable::IDrawable(std::string path) :
	_imgPath(path), _texture(NULL)
{}

IDrawable::~IDrawable()
{}

void IDrawable::loadTexture()
{

}

void IDrawable::addToDrawQueue()
{}