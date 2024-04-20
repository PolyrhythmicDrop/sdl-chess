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

// Method Definitions

/// <summary>
/// Initializes the texture variables to default values.
/// </summary>
void Texture::initTexture()
{
	// Initialize variables
	_texture = NULL;
	_renderer = NULL;
	_width = 0;
	_height = 0;

}


Texture::~Texture()
{
	freeTexture();
}


bool Texture::loadTextureFromSurface(std::string path)
{
	// Success flag
	bool success = true;

	//Get rid of pre-existing texture, if any
	freeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		//Create texture from surface pixels
		_texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
		if (_texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			success = false;
		}
		else
		{
			//Get image dimensions and set them to texture
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		return success;
	}
}

bool Texture::loadTextureFromImage(std::string path)
{
	bool success = false;
	
	// Free the existing texture, if any
	freeTexture();
	
	// Load an image at the specified path to a texture.
	_texture = IMG_LoadTexture(_renderer, path.c_str());	

	// Check that texture loaded properly
	if (_texture != NULL)
	{
		success = true;
	}

	return success;
}

void Texture::renderTexture(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, _width, _height };
	SDL_RenderCopy(_renderer, _texture, NULL, &renderQuad);
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

int Texture::getTextureWidth()
{
	return _width;
}

int Texture::getTextureHeight()
{
	return _height;
}

