#include "Texture.h"

/// <summary>
/// Default constructor for the texture wrapper
/// </summary>
Texture::Texture() 
	: _loadedTexture{ NULL }
{};

Texture::~Texture()
{
	freeTexture();
	std::cout << "Texture destructed!\n";
}


// Method Definitions

SDL_Texture* Texture::loadTextureFromImage(std::string path)
{
	bool success = false;
	
	// Free the existing texture, if any
	freeTexture();

	// Get the renderer
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	
	// Load an image at the specified path to a texture.
	_loadedTexture = IMG_LoadTexture(renderer, path.c_str());

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

