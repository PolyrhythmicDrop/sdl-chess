#include "Texture.h"

/// <summary>
/// Default constructor for the texture wrapper
/// </summary>
/// <param name="renderer">The renderer to render the texture with.</param>
Texture::Texture(Renderer* renderer) 
	: _renderer{renderer}, _sdlTexture {NULL}
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
	
	// Load an image at the specified path to a texture.
	SDL_Texture* newTexture = IMG_LoadTexture(_renderer->GetRenderer(), path.c_str());

	_sdlTexture = newTexture;

	return _sdlTexture;
}

SDL_Texture* Texture::getTexture()
{
	return _sdlTexture;
}


void Texture::freeTexture()
{
	// Free texture if it exists
	if (getTexture() != NULL)
	{
		SDL_DestroyTexture(_sdlTexture);
		_sdlTexture = NULL;		
	}
}

