#include "StaticImage.h"

StaticImage::StaticImage(std::string name, std::string path) :
	_name(name), _imgPath(path)
{
	_texture = NULL;
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
	dim dim = { this->_x, this->_y, this->_width, this->_height };
	this->dimensions = dim;
	SDL_Rect rect = {this->dimensions.x, this->dimensions.y, this->dimensions.w, this->dimensions.h };
	_srcRect = rect;
	_destRect = rect;
	std::cout << "New static image, " << _name << " created!\n";
}

StaticImage::~StaticImage()
{
	std::cout << _name << " destructed!\n";
}

void StaticImage::assignTexture(Texture* loader)
{
	_texture = loader->loadTextureFromImage(_imgPath);
	std::cout << "Texture loaded to " << _name << "!\n";
}

void StaticImage::draw()
{

}



