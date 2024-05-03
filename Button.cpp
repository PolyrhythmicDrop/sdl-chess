#include "Button.h""
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <iostream>

// Constructor, initialize values
Button::Button(std::string name, std::string imgPath) :
	_buttonName(name), _buttonPath(imgPath)
{
	_buttonTexture = NULL;
	_buttonRect;
	_buttonW = 0;
	_buttonH = 0;
	_buttonX = 0;
	_buttonY = 0;
}

SDL_Texture* Button::getButtonTexture()
{
	return _buttonTexture;
}

void Button::setButtonTexture(SDL_Texture* texture)
{
	_buttonTexture = texture;
}

std::string Button::getButtonPath()
{
	return _buttonPath;
}

void Button::setButtonDimensions(int x, int y, int width, int height)
{
	SDL_Rect buttonRect = { x, y, width, height };
	/*
	button->w = width;
	button->h = height;
	button->x = x;
	button->y = y;
	*/
	
	_buttonRect = buttonRect;
	_buttonW = buttonRect.w;
	_buttonH = buttonRect.h;
	//std::cout << button.w << button.h;

}


SDL_Rect Button::getButtonSourceRect()
{
	return _buttonRect;
}

std::string Button::getButtonName()
{
	return _buttonName;
}

void Button::setButtonWidth(int width)
{
	_buttonW = width;
}

int Button::getButtonWidth()
{
	return _buttonW;
}

void Button::setButtonHeight(int height)
{
	_buttonH = height;
}

int Button::getButtonHeight()
{
	return _buttonH;
}

void Button::setButtonX(int x)
{
	_buttonX = x;
}

int Button::getButtonX()
{
	return _buttonX;
}

void Button::setButtonY(int y)
{
	_buttonY = y;
}

int Button::getButtonY()
{
	return _buttonY;
}