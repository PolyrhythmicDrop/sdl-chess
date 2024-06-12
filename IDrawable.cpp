#include "IDrawable.h"

IDrawable::IDrawable() :
	_drawDimensions({0, 0, 0, 0}),
	_zIndex(0),
	_currentTexture(nullptr),
	_draw(false)
{}

SDL_Texture*& IDrawable::getCurrentTexture()
{
	return _currentTexture;
}

const SDL_Rect& IDrawable::getDrawDimensions()
{
	return _drawDimensions;
}

void IDrawable::setDrawDimensions(int x, int y, int w, int h)
{
	_drawDimensions = { x, y, w, h };
}

void IDrawable::setDrawPosition(int x, int y)
{
	_drawDimensions.x = x;
	_drawDimensions.y = y;
}

void IDrawable::setDrawScale(int w, int h)
{
	_drawDimensions.w = w;
	_drawDimensions.h = h;
}

void IDrawable::setDrawScaleByTexture()
{
	SDL_QueryTexture(_currentTexture, NULL, NULL, &_drawDimensions.w, &_drawDimensions.h);
}

const int& IDrawable::getZ()
{
	return _zIndex;
}

void IDrawable::setZ(int z)
{
	_zIndex = z;
}
