#pragma once
#include "IDrawable.h"
#include "Texture.h"
#include <memory>

class IDrawable;

class GraphicsComponent: public IDrawable
{
private:

	std::unique_ptr<Texture> _textureLoader;
	
	std::string _imgPath;	

public:
	
	GraphicsComponent();

	~GraphicsComponent();

	void setImgPath(std::string path);

	void loadTexture();

	GraphicsComponent* getGraphicsComponent();

};

