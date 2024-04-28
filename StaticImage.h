#pragma once
#include "GameObject.h"
#include "IDrawable.h"
#include <SDL.h>
#include <stdio.h>

class StaticImage : public GameObject, public IDrawable
{
private:

	std::string _name;
	std::string _imgPath;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	int _x;
	int _y;
	int _width;
	int _height;
	
	
public:

	dim dimensions;

	StaticImage(std::string name, std::string path);

	~StaticImage();

	void assignTexture(Texture* loader);

	void draw();


};

