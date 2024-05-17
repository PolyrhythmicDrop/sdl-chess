#include "Texture.h"
#include "easylogging++.h"

/// <summary>
/// Default constructor for the texture wrapper
/// </summary>
Texture::Texture() 
	: _loadedTexture{ NULL }
{};

Texture::~Texture()
{
	freeTexture();
	LOG(INFO) << "Texture destructed!";
}


// Method Definitions

SDL_Texture* Texture::loadTextureFromImage(std::string path)
{
	bool success = false;
	
	// Free the existing texture, if any
	freeTexture();
	
	// Load an image at the specified path to a texture.
	_loadedTexture = IMG_LoadTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), path.c_str());

	return _loadedTexture;
}

SDL_Texture* Texture::getTexture()
{
	return _loadedTexture;
}


void Texture::freeTexture()
{
	// Free texture if it exists
	if (_loadedTexture != NULL)
	{
		SDL_DestroyTexture(_loadedTexture);
		_loadedTexture = NULL;		
	}
	
}

