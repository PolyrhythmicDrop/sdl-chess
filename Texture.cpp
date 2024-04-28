#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Window.h"
#include <array>
#include <iostream>

/// <summary>
/// Default constructor for the texture wrapper
/// </summary>
/// <param name="renderer">The renderer to render the texture with.</param>
Texture::Texture(SDL_Renderer* renderer) 
	: _renderer {renderer}, _texture {NULL}, _width {0}, _height {0}
{};

Texture::~Texture()
{
	freeTexture();
}


// Method Definitions

SDL_Texture* Texture::loadTextureFromImage(std::string path)
{
	bool success = false;
	
	// Free the existing texture, if any
	freeTexture();
	
	// Load an image at the specified path to a texture.
	SDL_Texture* newTexture = IMG_LoadTexture(_renderer, path.c_str());	

	_texture = newTexture;

	return _texture;
}

SDL_Texture* const Texture::getTexture()
{
	return _texture;
}


void Texture::freeTexture()
{
	// Free texture if it exists
	if (_texture != NULL)
	{
		SDL_DestroyTexture(_texture);
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

